#include "fightingchapter.h"

#include <cassert>
#include <sstream>
#include <iostream>


#include "character.h"
#include "chapter.h"
#include "dice.h"
#include "helper.h"

FightingChapter::FightingChapter(Chapter& chapter)
  : m_chapter{chapter},
    m_escape_chapter{-1},
    m_fight_sequentially{true},
    m_monsters{},
    m_rounds_to_escape{1000},
    m_verbose{false}
{

}

void FightingChapter::AddMonster(const Monster& monster)
{
  m_monsters.push_back(monster);
}

void FightingChapter::Do(Character& character) const
{

  if (DoFightSequentially())
  {
    DoFight(GetMonsters(),character);
  }
  else
  {
    DoFightTwoMonsters(GetMonsters(),character);
  }
  if (HasItem(character, Item::silver_scorpion_brooch) && !IsDead(character))
  {
    character.ChangeCondition(1);
  }
}

void FightingChapter::DoFight(std::vector<Monster> monsters, Character& character) const
{
  for (auto monster: monsters)
  {
    const int n_chapters_before{static_cast<int>(character.GetChapters().size())};

    DoFight(monster,character);

    const int n_chapters_after{static_cast<int>(character.GetChapters().size())};
    if (n_chapters_after != n_chapters_before)
    {
      //Character escaped
      return;
    }

    if (IsDead(character)) return;
  }
}

void FightingChapter::DoFightTwoMonsters(std::vector<Monster> monsters,Character& character) const
{
  const Helper h;
  //Fight both
  assert(monsters.size() == 2);
  const std::string monster_name_0{h.ToPretty(monsters[0].GetName())};
  const std::string monster_name_1{h.ToPretty(monsters[1].GetName())};
  for (int round=0; ; ++round)
  {
    if (IsDead(character)) { return; }
    if (monsters[0].IsDead())
    {
      m_chapter.ShowText("You defeated the " + monster_name_0 + "!\n");
      character.AddHasFought(monsters[0].GetName()); //Must be raw name
      break;
    }

    {
      std::stringstream s;
      s
        << '\n'
        << "Fight round #" << round << '\n'
        << "You " << character.GetSkill() << " "
        << character.GetCondition() << "/"
        << character.GetInitialCondition() << '\n'
        << monster_name_0 << " "
        << monsters[0].GetSkill() << " "
        << monsters[0].GetCondition() << "/"
        << monsters[0].GetInitialCondition() << '\n'
        << monster_name_1 << " "
        << monsters[1].GetSkill() << " "
        << monsters[1].GetCondition() << "/"
        << monsters[1].GetInitialCondition() << '\n'
        << "Fight round #" << round
        << '\n'
      ;
      m_chapter.ShowText(s.str());
    }

    {
      const int monster_attack{monsters[0].CalcAttackStrength()};
      const int player_attack{character.CalcAttackStrength()};
      if (player_attack > monster_attack)
      {
        m_chapter.ShowText("You hit the " + monster_name_0 + ".\n");
        m_chapter.ShowText("Do you want to use luck?\n");

        const auto options = CreateYesNoOptions();
        const Option selected_option{m_chapter.RequestOption(options)};
        assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
          || selected_option.GetConsequence().GetType() == ConsequenceType::no
        );
        int damage = 2;
        if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
        {
          const bool has_luck{character.TestLuck()};
          damage += (has_luck ? -1 : 1);
        }
        monsters[0].ChangeCondition(-damage);
        m_chapter.ShowText(
          "You did the " + monster_name_0
          + " " + h.ToStr(damage) + " points of damage \n"
        );
      }
      else if (player_attack < monster_attack)
      {
        if(character.GetAutoAttack()==false)
        {

            m_chapter.ShowText("You were hit by the " + monster_name_0 + ".\n");
            m_chapter.ShowText("Do you want to use luck?\n");

            const auto options = CreateYesNoOptions();
            const Option selected_option{m_chapter.RequestOption(options)};
            assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
              || selected_option.GetConsequence().GetType() == ConsequenceType::no
            );
            int damage{monsters[0].GetAttackDamage()};
            if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
            {
              const bool has_luck{character.TestLuck()};
              damage -= ( (damage/2) * (has_luck ? 1 : -1) );
            }
            character.ChangeCondition(-damage);
            m_chapter.ShowText(
              "The " + monster_name_0
              + " hit you with " + h.ToStr(damage) + " points of damage \n"
            );
         }
      }
      else
      {
        m_chapter.ShowText("No damage was dealt.\n");
      }
    }
    //Second monster
    {
      const int monster_attack{monsters[1].CalcAttackStrength()};
      const int player_attack{character.CalcAttackStrength()};
      if (player_attack >= monster_attack)
      {
        m_chapter.ShowText("You resisted the " + monster_name_1 + ".\n");
      }
      else if (player_attack < monster_attack)
      {
        int damage{monsters[1].GetAttackDamage()};
        if(character.GetAutoAttack()==false)
        {
            m_chapter.ShowText("You were hit by the " + monster_name_1 + ".\n");
            m_chapter.ShowText("Do you want to use luck?\n");

            const auto options = CreateYesNoOptions();
            const Option selected_option{m_chapter.RequestOption(options)};
            assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
              || selected_option.GetConsequence().GetType() == ConsequenceType::no
            );


            if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
            {
              const bool has_luck{character.TestLuck()};
              damage += ( (damage/2) * (has_luck ? -1 : 1) );
            }
         }
        character.ChangeCondition(-damage);
        m_chapter.ShowText(
          "The " + monster_name_1
          + " hit you with " + h.ToStr(damage) + " points of damage \n"
        );
      }
    }
    m_chapter.Wait();

    if (round >= this->m_rounds_to_escape)
    {
      m_chapter.ShowText("Do you want to escape?\n");
      const auto options = CreateYesNoOptions();
      const Option selected_option{m_chapter.RequestOption(options)};
      assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
        || selected_option.GetConsequence().GetType() == ConsequenceType::no
      );
      if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
      {
        m_chapter.ShowText("You escaped and took 2 damage.\n");
        assert(m_escape_chapter > -1);
        character.SetChapter(m_escape_chapter);
        character.ChangeCondition(-2);
        return;
      }
    }
  }

  //Fight the remaining monster normally
  DoFight(monsters[1],character);
}


void FightingChapter::DoFight(Monster monster,Character& character) const
{
  const Helper h;
  const std::string monster_name{h.ToPretty(monster.GetName())};

  for (int round = 1; ; ++round)
  {
    if (IsDead(character)) break;
    if (monster.IsDead()) break;
    {
      std::stringstream s;
      s
        << '\n'
        << "Fight round #" << round << '\n'
        << "You " << character.GetSkill() << " "
        << character.GetCondition() << "/"
        << character.GetInitialCondition() << '\n'
        << monster_name << " "
        << monster.GetSkill() << " "
        << monster.GetCondition() << "/"
        << monster.GetInitialCondition() << '\n'
      ;
      m_chapter.ShowText(s.str());
    }

    const int monster_attack{monster.CalcAttackStrength()};
    const int player_attack{character.CalcAttackStrength()};

    {
      std::stringstream s;
      s
        << "You attack with strength " << player_attack << '\n'
        << monster_name << " attacks with strength " << monster_attack << '\n'
      ;
      m_chapter.ShowText(s.str());
    }

    if (player_attack > monster_attack)
    {
      m_chapter.ShowText("You hit the " + monster_name + ".\n");
      int damage{2};
      if (monster.GetCondition() > damage)
      {
        if(character.GetAutoAttack()==false)
        {
            m_chapter.ShowText("Do you want to use luck?\n");
            const auto options = CreateYesNoOptions();
            const Option selected_option{m_chapter.RequestOption(options)};
            assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
              || selected_option.GetConsequence().GetType() == ConsequenceType::no
            );
            if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
            {
              const bool has_luck{character.TestLuck()};
              damage += has_luck ? 1 : -1;
            }
         }
      }
      monster.ChangeCondition(-damage);
      m_chapter.ShowText("You did the " + monster_name
        + " " + h.ToStr(damage) + " points of damage \n"
      );
    }
    else if (player_attack < monster_attack)
    {
      m_chapter.ShowText("You were hit by the " + monster_name + ".\n");
      int damage{monster.GetAttackDamage()};
      if (character.GetCondition() >= monster.GetAttackDamage())
      {
        if(character.GetAutoAttack()==false)
        {
            m_chapter.ShowText("Do you want to use luck?\n");

            const auto options = CreateYesNoOptions();
            const Option selected_option{m_chapter.RequestOption(options)};
            assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
              || selected_option.GetConsequence().GetType() == ConsequenceType::no
            );

            if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
            {
              const bool has_luck{character.TestLuck()};
              damage += ( (damage / 2 ) * (has_luck ? -1 : 1) );
            };
        }
      }
      character.ChangeCondition(-damage);
      m_chapter.ShowText("The " + monster_name
        + " did " + h.ToStr(damage) + " points of damage \n"
      );
    }
    else
    {
      m_chapter.ShowText("No damage was dealt.\n");
    }

    m_chapter.Wait();

    if (IsDead(character)) break;
    if (monster.IsDead()) break;

    //Fire breath
    if (monster.HasFireBreath())
    {
      m_chapter.ShowText("The monster uses its fiery breath....\n");
      m_chapter.Wait();
      if (Dice::Get()->Throw() <= 3)
      {
        m_chapter.ShowText("The fire hits you!\n");
        m_chapter.Wait();
        character.ChangeCondition(-2);
      }
      else
      {
        m_chapter.ShowText("The fire missed you!\n");
        m_chapter.Wait();
      }
    }

    if (IsDead(character)) break;
    if (monster.IsDead()) break;

    if (round >= this->m_rounds_to_escape && character.GetCondition() > 2)
    {
      m_chapter.ShowText("Do you want to escape?\n");
      const auto options = CreateYesNoOptions();
      const Option selected_option{m_chapter.RequestOption(options)};
      assert(selected_option.GetConsequence().GetType() == ConsequenceType::yes
        || selected_option.GetConsequence().GetType() == ConsequenceType::no
      );
      if (selected_option.GetConsequence().GetType() == ConsequenceType::yes)
      {
        break;
      }
    }
  }

  if (IsDead(character))
  {
    m_chapter.ShowText("The " + monster_name + " defeated you.\n");
  }
  else if (monster.IsDead())
  {
    character.AddHasFought(monster.GetName());
    assert(character.HasFought(monster.GetName()));
    m_chapter.ShowText("You defeated the " + monster_name + "!\n");
  }
  else
  {
    assert(m_escape_chapter > -1);
    assert(character.GetCondition() > 2);
    character.ChangeCondition(-2);
    m_chapter.ShowText("You escaped and took 2 damage.\n");
    character.SetChapter(m_escape_chapter);
    return;
  }
  m_chapter.Wait();
}

void FightingChapter::SetEscapeToChapter(const int escape_to_chapter)
{
  m_escape_chapter = escape_to_chapter;
  assert(m_escape_chapter > 0);

}

void FightingChapter::SetRoundsToEscape(const int rounds_to_escape)
{
  m_rounds_to_escape = rounds_to_escape;
  assert(m_rounds_to_escape >= 0);
}

void FightingChapter::SetVerbose(const bool verbose) const noexcept
{
  m_verbose = verbose;
}
