#include "ai.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <memory>

#include "chapter.h"
#include "dice.h"
#include "game.h"
#include "helper.h"
#include "option.h"

Ai::Ai()
  :
    m_distribution{std::uniform_real_distribution<double>(0.0,1.0)},
    m_engine(0),
    m_game{nullptr},
    m_keys{},
    m_payoffs{},
    m_silent{true},
    m_tally{}
{
  m_tally[Item::black_pearls] = 0;
  m_tally[Item::hags_hair] = 0;
  m_tally[Item::lotus_flower] = 0;
  m_tally[Item::silver_arrow] = 0;
  m_tally[Item::tattoo] = 0;
}


void Ai::CreateGraph() const noexcept
{
  const std::string filename_base{"Payoffs"};
  const std::string dot_filename{filename_base + ".dot"};
  const std::string png_filename{filename_base + ".png"};
  std::ofstream f(dot_filename);

  f << "digraph CityOfThievesPayoffs {\n";
  for (int i=1; i!=450; ++i)
  {
    try
    {
      const Chapter chapter(i);
      //Label node according to chapter type
      std::string node_color = "black";
      switch (chapter.GetType())
      {
        case ChapterType::fight: node_color = "red"; break;
        case ChapterType::test_your_luck: node_color = "blue"; break;
        case ChapterType::test_your_skill: node_color = "green"; break;
        default: break; //OK
      }
      //Shape for special chapter
      std::string shape{"ellipse"};
      switch (i)
      {
        case 7: case 111: //Black pearls
        case 191: case 237: //Lotus flower
        case 82: case 303: //Hag's hair
        case 42: case 85: //Silver arrow
        case 279: //Tattoo
        case 163: //Ring of the golden eye
          shape = "doublecircle";
          break;
        default: break;
      }
      f << i
        << "["
        << "label =\""
        << Helper().ToStr(chapter.GetChapterNumber())
        << "\", shape = " << shape
        << "];\n"
      ;

      if (chapter.GetNextChapter() != -1)
      {
        f << i << "->" << chapter.GetNextChapter() << ";\n";
      }
      else if (!chapter.GetFighting().GetMonsters().empty())
      {

        if (chapter.GetFighting().GetEscapeToChapter() != -1)
        {
          f << i << "->" << chapter.GetFighting().GetEscapeToChapter() << " [ label = \"Escape\"];\n";
        }
      }
      else if (!chapter.GetLuck().GetLuckText().empty())
      {
        f << i << "->" << chapter.GetLuck().GetLuckChapter() << " [ label = \"Luck\"];\n";
        f << i << "->" << chapter.GetLuck().GetNoLuckChapter() << " [ label = \"No luck\"];\n";
      }
      else if (!chapter.GetOptions().GetOptions().empty())
      {
        for (const auto& option: chapter.GetOptions().GetOptions())
        {
          //No payoff
          //f << i << "->" << option.GetNextChapter() << " [ label = \"Choice\"];\n";
          f << i << "->" << option.GetNextChapter() << " [ label = \""
            << GetPayoff(option.GetText()) <<  "\"];\n";
        }
      }
      else if (!chapter.GetSkill().GetSkillText().empty())
      {
        f << i << "->" << chapter.GetSkill().GetSkillConsequence().GetNextChapter() << " [ label = \"Skill\"];\n";
        f << i << "->" << chapter.GetSkill().GetNoSkillConsequence().GetNextChapter() << " [ label = \"No skill\"];\n";
      }
      else if (chapter.GetType() == ChapterType::game_lost)
      {
        f << i << "-> GameOver;\n";
      }
      else if (chapter.GetType() == ChapterType::game_won)
      {
        f << i << "-> GameWon;\n";
      }
    }
    catch (const std::logic_error&)
    {
      //f << i << ": FAIL" << std::endl;
    }
    catch (const std::runtime_error&)
    {
      //f << i << ": not present" << std::endl;
    }
  }
  f << "}\n";
  f.close();
  {
    std::stringstream cmd;
    cmd << "dot -Tpng " << dot_filename << " > " << png_filename;
    const int error{std::system(cmd.str().c_str())};
    assert(!error);
    if (error) {;}
  }
}

double Ai::CalcFinalPayoff(const Character& character) const noexcept
{
  assert(character.GetChapters().size() > 1 && "Cannot die in chapter 1");

  if (character.HasItem(Item::black_pearls)) ++m_tally[Item::black_pearls];
  if (character.HasItem(Item::silver_arrow)) ++m_tally[Item::silver_arrow];
  if (character.HasItem(Item::hags_hair)) ++m_tally[Item::hags_hair];
  if (character.HasItem(Item::lotus_flower)) ++m_tally[Item::lotus_flower];
  if (character.HasItem(Item::tattoo)) ++m_tally[Item::tattoo];

  //The rarer an item is discovered, the higher its value
  const int sum{
    std::accumulate(std::begin(m_tally),std::end(m_tally),0,
    [](const int init,const auto& p) { return init + p.second; }
    )
  };
  const double average{static_cast<double>(sum) / 5.0 };

  std::map<Item,double> values;
  values[Item::black_pearls] = average  / static_cast<double>(m_tally[Item::black_pearls]);
  values[Item::silver_arrow] = average  / static_cast<double>(m_tally[Item::silver_arrow]);
  values[Item::hags_hair] = average  / static_cast<double>(m_tally[Item::hags_hair]);
  values[Item::lotus_flower] = average  / static_cast<double>(m_tally[Item::lotus_flower]);
  values[Item::tattoo] = average  / static_cast<double>(m_tally[Item::tattoo]);

  const auto visited = character.GetChapters();
  const bool got_in_city{std::count(std::begin(visited),std::end(visited),74) == 1 ? true : false};
  const bool got_in_forest{std::count(std::begin(visited),std::end(visited),201) == 1 ? true : false};

  const double final_payoff{
    std::pow(
        (character.HasItem(Item::black_pearls) ? values[Item::black_pearls] : 0.0)
      + (character.HasItem(Item::lotus_flower) ? values[Item::lotus_flower] : 0.0)
      + (character.HasItem(Item::hags_hair)    ? values[Item::hags_hair] : 0.0)
      + (character.HasItem(Item::tattoo)       ? values[Item::tattoo] : 0.0)
      + (character.HasItem(Item::silver_arrow) ? values[Item::silver_arrow] : 0.0)
      + (character.GetCurrentChapter() == 400  ? 1.0 : 0.0) //Won the game
      + (got_in_city ? 1.0 : 0.0)
      + (got_in_forest ? 1.0 : 0.0)
    ,2.0)
  };
  if (character.GetCurrentChapter() == 400) { std::clog << "Finished game" << std::endl; }

  /*
  if (!character.HasItem(Item::black_pearls)) return 0.0;
  //if (!character.HasItem(Item::potion_of_mind_control)) return 4.0;
  if (!character.HasItem(Item::silver_arrow)) return 4.0;
  if (!character.HasItem(Item::hags_hair)) return 16.0;
  if (!character.HasItem(Item::lotus_flower)) return 64.0;
  if (!character.HasItem(Item::tattoo)) return 256.0;
  if (!character.GetCurrentChapter() == 400) return 1024.0;
  return 4096.0;
  */
  /*
  const double final_payoff{
    std::pow(
        (character.HasItem(Item::black_pearls) ? 1.0 : 0.0)
      + (character.HasItem(Item::lotus_flower) ? 1.0 : 0.0)
      + (character.HasItem(Item::hags_hair)    ? 1.0 : 0.0)
      + (character.HasItem(Item::tattoo)       ? 1.0 : 0.0)
      + (character.HasItem(Item::silver_arrow) ? 1.0 : 0.0)
      + (character.GetCurrentChapter() == 400  ? 1.0 : 0.0) //Won the game
    ,2.0)
  };
  */
  return final_payoff;
}

double Ai::GetPayoff(const std::string& option_text) const noexcept
{
  if (option_text == CreateShowInventoryOption().GetText()) return 0.0;

  const auto iter
   = std::find_if(
       std::begin(m_payoffs),
       std::end(m_payoffs),
       [option_text](const PayoffPair& pair)
       {
         return pair.first == option_text;
       }
     );
  if (iter == std::end(m_payoffs))
  {
    const_cast<Ai*>(this)->m_payoffs.push_back(PayoffPair(option_text,1.0));
    return GetPayoff(option_text);
  }
  assert(iter != std::end(m_payoffs));
  return iter->second;
}


void Ai::SetFinalPayoff(const Payoff& final_payoff)
{
  const bool verbose{false};
  assert(!m_keys.empty());
  double weight{1.0};
  for (int i=0; ; ++i)
  {
    weight *= 0.9;
    assert(!m_keys.empty());
    const auto key = m_keys.back();
    const double current_key_payoff{GetPayoff(key)};
    const double new_chapter_payoff{
      current_key_payoff + (weight * (final_payoff - current_key_payoff))
    };
    assert(Helper().IsBetween(new_chapter_payoff,current_key_payoff,final_payoff));
    if (verbose)
    {
      std::clog << "Assign payoff to key: " << key << std::endl;
      std::clog << " * Final payoff: " << final_payoff << std::endl;
      std::clog << " * Previous payoff: " << current_key_payoff << std::endl;
      std::clog << " * New payoff: " << new_chapter_payoff << std::endl;
    }
    SetPayoff(key,new_chapter_payoff);
    m_keys.pop_back();
    if (m_keys.empty()) break;
  }
  m_keys.clear();
}

void Ai::SetPayoff(const Key& key, const Payoff& payoff)
{
  assert(payoff >= 0.0);

  auto iter = std::find_if(
    std::begin(m_payoffs),
    std::end(m_payoffs),
    [key](const PayoffPair& pair)
    {
      return pair.first == key;
    }
  );
  assert(iter != std::end(m_payoffs));
  iter->second = payoff;
}

void Ai::Start()
{
  Helper().CoutNl("SOLVING THE GAME");

  for (int i=1; ; ++i)
  {
    //if i equals 1,10,100,1000,etc...
    if (i % 10000 == 0)
    //if (static_cast<int>(std::log10(i)) != static_cast<int>(std::log10(i-1)))
    {
      { std::stringstream s; s << "i: " << i << std::endl; Helper().CoutNl(s.str()); }
      this->CreateGraph();
      Helper().CoutNl("DONE");
    }

    const int skill = 3 + Dice::Get()->Throw();
    const int condition = Dice::Get()->Throw() + Dice::Get()->Throw();
    const int luck = 6 + Dice::Get()->Throw();
    const bool autoAttack{true};
    const Character character(skill,condition,luck,Item::luck_potion, autoAttack);
    Game game(51,character);
    m_game = &game; /// !OCLINT game is only used in scope

    game.SetObserver(this);

    //game.SetChapter(259);

    while (1)
    {
      game.DoChapter();
      if (game.HasLost() || game.HasWon()) break;
    }

    SetFinalPayoff(CalcFinalPayoff(game.GetCharacter()));
    if (game.HasWon()) { break; }
  }
  m_game = nullptr;
  std::cout << "FINISHED THE GAME, CREATING GRAPH" << '\n';
  this->CreateGraph();
}

std::ostream& operator<<(std::ostream& os, const Ai& ai)
{
  const auto payoffs = ai.GetPayoffs();
  for (const auto& payoff: payoffs)
  {
    os << "(" << payoff.first << "," << payoff.second << ")\n";
  }
  return os;
}

Option Ai::RequestOption(const std::vector<Option>& options)
{
  for (const auto& option: options)
  {
    ShowText(" * " + option.GetText() + "\n");
  }
  assert(!options.empty());
  if (options.size() == 1) return options[0];
  if (options[0].GetConsequence().GetType() == ConsequenceType::no)
  {
    return options[0]; //Always say no
  }

  std::vector<double> expected_payoffs;
  std::transform(
    std::begin(options),
    std::end(options),
    std::back_inserter(expected_payoffs),
    [this](const Option& option)
    {
      const auto text = option.GetText();
      const double payoff{GetPayoff(text)};
      assert(payoff >= 0.0);
      return payoff;
    }
  );

  const int n_options{static_cast<int>(options.size())};

  const bool choose_probabilisticly{true};
  if (choose_probabilisticly)
  {
    const double sum{std::accumulate(std::begin(expected_payoffs),std::end(expected_payoffs),0.0)};
    if (sum != 0.0)
    {
      double f{m_distribution(m_engine) * sum};
      for (int i=0; i!=n_options; ++i)
      {
        const auto text = options[i].GetText();
        if (f < GetPayoff(text))
        {
          m_keys.push_back(text);
          return options[i];
        }
        f -= GetPayoff(text);
      }
      //Should not get here often
    }
    //Choose first option
    m_keys.push_back(options[0].GetText());
    return options[0];
  }
  //Choose best
  int best_option{0};
  double expected_payoff{GetPayoff(options[0].GetText())};
  for (int i=1; i!=n_options; ++i)
  {
    double this_expected_payoff{GetPayoff(options[i].GetText())};
    if (this_expected_payoff > expected_payoff)
    {
      best_option = i;
      expected_payoff = this_expected_payoff;
    }
  }
  m_keys.push_back(options[best_option].GetText());
  return options[best_option];
}

void Ai::ShowText(const std::string& text)
{
  if (m_silent) { return; }

  const int n_chars{60};
  int pos = 0;
  for (const char c: text)
  {
    if (c == '\n') pos = -1;
    else if (c == ' ' && pos > n_chars) { pos = 0; std::cout << '\n'; continue; }
    else if (c == ' ' && pos == 0) { continue; }
    std::cout << c;
    ++pos;
    std::cout.flush();
  }
}

void Ai::Wait()
{
  //Continue
}


void SolveGame()
{
  Ai ai;
  ai.Start();
}
