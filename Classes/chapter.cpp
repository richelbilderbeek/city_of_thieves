#include "chapter.h"

#include <cassert>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ai.h"
#include "dice.h"
#include "getfile.h"
#include "helper.h"

Chapter::Chapter(const int chapter_number)
  :
    m_ball_game_chapter{*this},
    m_bye_text{},
    m_consequence{},
    m_chapter_number{chapter_number},
    m_chapter_type{ChapterType::normal},
    m_dice_game_chapter{*this},
    m_fighting_chapter{FightingChapter(*this)},
    m_game_lost_chapter{this},
    m_game_won_chapter{this},
    m_luck_chapter(*this),
    m_observer{nullptr},
    m_options_chapter{},
    m_pawn_shop_chapter(this),
    m_pill_game_chapter{*this},
    m_shop_chapter{this},
    m_skill_chapter{*this},
    m_text{},
    m_verbose{false}
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
  Helper h;

  if (m_verbose) { std::clog << __func__ << std::endl; }

  #ifdef USE_TEXT_FILES_FOR_INPUT
  const std::string filename{h.GetFilesFolder() + h.ToStr(chapter_number) + ".txt"};
  if (!h.IsRegularFile(filename))
  {
    std::stringstream msg;
    msg << __func__ << ": ERROR: File " << filename << " does not exist";
    Helper().Cout(msg.str());
    throw std::runtime_error(msg.str());
  }
  const std::vector<std::string> lines{h.FileToVector(filename)};
  #else
  const std::vector<std::string> lines(1,GetFile(h.ToStr(chapter_number)));
  #endif
  std::stringstream s;
  std::copy(std::begin(lines),std::end(lines),std::ostream_iterator<std::string>(s," "));

  m_text = h.ReadText(s);

  m_chapter_type = ReadChapterType(s);

  switch (m_chapter_type)
  {
    case ChapterType::game_lost: return;
    case ChapterType::game_won: return;
    default: break;
  }

  while (!s.eof())
  {
    const std::string str{h.ReadString(s)};
    if (str.empty())
    {
      break;
    }
    else if (str == "Bye" || str == "bye")
    {
      m_bye_text = h.ReadText(s);
    }
    else if (str == "Change" || str == "change")
    {
      m_consequence.Add(ParseConsequence(s));
    }
    else if (str == "Escape" || str == "escape")
    {
      GetFighting().SetRoundsToEscape(h.ReadInt(s));
      GetFighting().SetEscapeToChapter(h.ReadInt(s));
    }
    else if (str == "Fight_both" || str == "fight_both")
    {
      GetFighting().SetFightSequentially(false);
    }
    else if (str == "Luck" || str == "luck")
    {
      assert(this->m_chapter_type == ChapterType::test_your_luck);
      const std::string luck_text{h.ReadText(s)};
      assert(!luck_text.empty());
      GetLuck().SetLuckText(luck_text);
      const std::string goto_str{h.ReadString(s)};
      assert(goto_str == "goto");
      const int luck_chapter{h.ReadInt(s)};
      assert(luck_chapter > 1);
      GetLuck().SetLuckChapter(luck_chapter);
    }
    else if (str == "Monster" || str == "monster")
    {
      this->m_chapter_type = ChapterType::fight;
      const Monster monster{ParseMonster(s)};
      GetFighting().AddMonster(monster);
    }
    else if (str == "Next_chapter" || str == "goto")
    {
      m_consequence.SetNextChapter(h.ReadInt(s));
    }
    else if (str == "No_luck" || str == "no_luck")
    {
      assert(this->m_chapter_type == ChapterType::test_your_luck);
      //s << std::noskipws; //Obligatory
      //Parse(s,' '); //You expect a space after a word
      const std::string no_luck_text{h.ReadText(s)};
      assert(!no_luck_text.empty());
      GetLuck().SetNoLuckText(no_luck_text);
      const std::string then{h.ReadString(s)};
      if (then == "change")
      {
        const Consequence no_luck_consequence{ParseConsequence(s)};
        GetLuck().SetNoLuckConsequence(no_luck_consequence);
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
      }
      else
      {
        assert(then == "goto");
      }
      const int no_luck_chapter{h.ReadInt(s)};
      assert(no_luck_chapter > 1);
      GetLuck().SetNoLuckChapter(no_luck_chapter);
    }
    else if (str == "No_skill" || str == "no_skill")
    {
      assert(this->m_chapter_type == ChapterType::test_your_skill);
      //Parse(s,' '); //You expect a space after a word
      const std::string no_skill_text{h.ReadText(s)};
      assert(!no_skill_text.empty());
      GetSkill().SetNoSkillText(no_skill_text);
      const std::string then_str{h.ReadString(s)};
      Consequence consequence;
      if (then_str == "goto")
      {
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else if (then_str == "change")
      {
        consequence = ParseConsequence(s);
        //Also read goto
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else
      {
        assert(!"Should not get here");
      }
      GetSkill().SetNoSkillConsequence(consequence);
    }
    else if (str == "Option" || str == "option")
    {
      const std::string option_text{h.ReadText(s)};
      const std::string t{h.ReadString(s)};
      if (t == "if")
      {
        const Condition condition{ParseCondition(s)};

        const std::string then_str{h.ReadString(s)};
        Consequence consequence;
        if (then_str == "goto")
        {
          consequence.SetNextChapter(h.ReadInt(s));
        }
        else if (then_str == "change")
        {
          consequence = ParseConsequence(s);
          //Also read goto
          const std::string goto_str{h.ReadString(s)};
          assert(goto_str == "goto");
          consequence.SetNextChapter(h.ReadInt(s));
        }
        else
        {
          assert(!"Should not get here");
        }
        Option option(option_text,consequence);
        option.SetCondition(condition);
        GetOptions().AddOption(option);
      }
      else if (t == "ifnot")
      {
        Condition condition;
        const std::string what{h.ReadString(s)};
        if (IsItem(what))
        {
          const Item item_not_needed{ToItem(what)};
          condition.AddItemNotNeeded(item_not_needed);
        }
        else
        {
          std::cerr << "Unknown item " << what << " in chapter " << chapter_number << std::endl;
          assert(!"Should not get here");
        }
        const std::string str_goto{h.ReadString(s)};
        assert(str_goto == "goto");
        Consequence consequence;
        consequence.SetNextChapter(h.ReadInt(s));
        Option option(option_text,consequence);
        option.SetCondition(condition);
        GetOptions().AddOption(option);
      }
      else if (t == "goto")
      {
        Consequence consequence;
        consequence.SetNextChapter(h.ReadInt(s));
        const Option option(option_text,consequence);
        GetOptions().AddOption(option);
      }
      else if (h.IsInt(t))
      {
        std::clog << "WARNING: goto omitted in chapter " << chapter_number << std::endl;
        //If no goto, just parse the number
        Consequence consequence;
        consequence.SetNextChapter(h.ToInt(t));
        const Option option(option_text,consequence);
        GetOptions().AddOption(option);
      }
      else
      {
        std::cerr << "Unknown option " << t << " in chapter " << chapter_number <<std::endl;
        assert(!"Should not get here");
      }
    }
    else if (str == "Random_monsters" || str == "random_monsters")
    {
      std::vector<Monster> monsters{ParseMonsters(s)};
      m_chapter_type = ChapterType::fight;
      const int which_monster_index{Dice::Get()->Throw() - 1};
      assert(which_monster_index >= 0);
      assert(which_monster_index < static_cast<int>(monsters.size()));
      const Monster monster{monsters[which_monster_index]};
      m_fighting_chapter.AddMonster(monster);
    }
    else if (str == "Sell_items" || str == "sell_items")
    {
      assert(this->m_chapter_type == ChapterType::pawn_shop);
      //m_chapter_type = ChapterType::pawn_shop;
      m_pawn_shop_chapter = ParsePawnShopChapter(s,this);
    }
    else if (str == "Shop_items" || str == "shop_items")
    {
      assert(this->m_chapter_type == ChapterType::shop);
      //m_chapter_type = ChapterType::shop;
      m_shop_chapter = ParseShopChapter(s,this);
    }
    else if (str == "Skill" || str == "skill")
    {
      assert(this->m_chapter_type == ChapterType::test_your_skill);
      this->m_chapter_type = ChapterType::test_your_skill;
      //Parse(s,' '); //You expect a space after a word
      const std::string skill_text{h.ReadText(s)};
      assert(!skill_text.empty());
      GetSkill().SetSkillText(skill_text);
      const std::string then_str{h.ReadString(s)};
      Consequence consequence;
      if (then_str == "goto")
      {
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else if (then_str == "change")
      {
        consequence = ParseConsequence(s);
        //Also read goto
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else
      {
        assert(!"Should not get here");
      }
      GetSkill().SetSkillConsequence(consequence);

    }

    else
    {
      std::cerr
        << "Chapter cannot parse chapter " << chapter_number  << '\n'
        << "Unknown string: " << str << '\n'
      ;
      assert(!"Should not get here");
    }
  }

}

void Chapter::Do(Character& character) const
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
  Helper h;

  assert(m_observer);
  character.SetObserver(m_observer);

  if (m_verbose) { std::clog << "The first text comes now" << std::endl; }

  ShowText("\n");

  #ifndef NDEBUG
  ShowText("CHAPTER " + h.ToStr(GetChapterNumber()) + "\n");
  #endif

  //Display the text line by line
  ShowText(m_text + "\n");

  if (m_verbose) { std::clog << "The first text has been" << std::endl; }


  if (GetType() == ChapterType::game_lost)
  {
    m_game_lost_chapter.Do(character);
    assert(character.IsDead());
    return;
  }
  else if (GetType() == ChapterType::game_won)
  {
    ShowText("\n");
    m_game_won_chapter.Do(character);
    ShowText("\n");
    return;
  }
  else if (GetType() == ChapterType::play_dice)
  {
    m_dice_game_chapter.Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::play_ball)
  {
    m_ball_game_chapter.Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::play_pill)
  {
    m_pill_game_chapter.Do(character);
    if (character.IsDead()) return;
    m_consequence.Apply(character);
  }
  //Options
  else if (!GetOptions().GetOptions().empty())
  {
    if (GetOptions().GetValidOptions(character).empty())
    {
      std::cerr
        << "ERROR: no valid options in chapter " << character.GetCurrentChapter()
        << std::endl
        << "Options:\n"
      ;
      assert(GetOptions().GetOptions().size() == 2);
    }
    while (1)
    {
      if (m_verbose) { std::clog << "Let the use choose a valid option" << std::endl; }

      auto options = GetOptions().GetValidOptions(character);

      //If there are options, add (1) showing inventory (2) eating provision (3) drinking potion
      if (options.size() > 1)
      {
        //Add to show the inventory
        options.push_back(CreateShowInventoryOption());
        if (character.GetProvisions() > 0) { options.push_back(CreateEatProvisionOption()); }
        if (character.HasPotion()) { options.push_back(CreateDrinkPotionOption()); }
      }

      if (m_verbose) { std::clog << "Do the request" << std::endl; }

      assert(m_observer);
      const auto chosen = m_observer->RequestOption(options);

      if (m_verbose) { std::clog << "Done the request" << std::endl; }

      ShowText("\n");
      if (chosen.GetConsequence().GetType() == ConsequenceType::show_inventory)
      {
        //Showing the inventory is trivial
        this->ShowText(character.ShowInventory());
        continue;
      }
      if (chosen.GetConsequence().GetType() == ConsequenceType::eat_provision)
      {
        character.ChangeProvisions(-1);
        character.ChangeCondition(4);
        continue;
      }
      if (chosen.GetConsequence().GetType() == ConsequenceType::drink_potion)
      {
        character.DrinkPotion();
        continue;
      }

      chosen.DoChoose(character);
      assert(m_consequence.GetNextChapter() == -1);

      //Only apply these consequences once
      m_consequence.Apply(character);
      break;
    }
  }
  else if (GetType() == ChapterType::fight)
  {
    const int n_chapters_before{static_cast<int>(character.GetChapters().size())};
    m_fighting_chapter.Do(character);
    if (character.IsDead())
    {
      m_game_lost_chapter.Do(character);
      return;
    }

    assert(m_consequence.GetNextChapter() > 0);
    const int n_chapters_after{static_cast<int>(character.GetChapters().size())};
    if (n_chapters_after != n_chapters_before)
    {
      //Player has escaped
      //Check that there are no other consequences that need to be applied
      assert(m_consequence.GetChangeArrows() == 0);
      assert(m_consequence.GetChangeCondition() == 0);
      assert(m_consequence.GetChangeGold() == 0);
      assert(m_consequence.GetChangeLuck() == 0);
      assert(m_consequence.GetChangeProvisions() == 0);
      assert(m_consequence.GetChangeSkill() == 0);
      assert(m_consequence.GetItemsToAdd().empty());
      assert(m_consequence.GetItemsToRemove().empty());
    }
    else
    {
      m_consequence.Apply(character);
    }
  }
  else if (GetType() == ChapterType::test_your_luck)
  {
    GetLuck().Do(character);
  }
  else if (GetType() == ChapterType::test_your_skill)
  {
    GetSkill().Do(character);
  }
  else if (GetType() == ChapterType::shop)
  {
    GetShop().Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::pawn_shop)
  {
    GetPawnShop().Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::normal)
  {
    //Nothing
    m_consequence.Apply(character);
  }
  else
  {
    assert(!"Should not get here");
  }

  if (character.IsDead())
  {
    m_game_lost_chapter.Do(character);
    return;
  }

  ShowText(m_bye_text);
}


Option Chapter::RequestOption(const std::vector<Option>& options) const
{
  assert(m_observer);
  return m_observer->RequestOption(options);
}

void Chapter::ShowText(const std::string& text) const
{
  if (m_verbose) { Helper().CoutNl(__func__); }

  assert(m_observer);
  m_observer->ShowText(text);
}

void Chapter::CharacterChanged(const Character& character) const
{
  assert(m_observer);
  m_observer->CharacterChanged(character);
}

void Chapter::Wait() const
{
  assert(m_observer);
  m_observer->Wait();
}

std::ostream& operator<<(std::ostream& os, const Chapter& chapter)
{
  os
    << "text: " << chapter.GetText() << '\n'
    << "# monsters: " << chapter.GetFighting().GetMonsters().size() << '\n'
  ;
  for (const auto& monster: chapter.GetFighting().GetMonsters())
  {
    os << monster << '\n';
  }
  os
    << "next_chapter: " << chapter.GetNextChapter() << '\n'
  ;
  return os;
}
