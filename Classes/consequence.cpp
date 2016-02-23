#include "consequence.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "character.h"
#include "dice.h"
#include "helper.h"

Consequence::Consequence()
  :
    m_add_items{},
    m_change_arrows{0},
    m_change_dex{0},
    m_change_gold{0},
    m_change_luck{0},
    m_change_provisions{0},
    m_change_sta{0},
    m_next_chapter{-1},
    m_remove_items{},
    m_type{ConsequenceType::normal}
{

}

void Consequence::Add(const Consequence& other)
{
  this->m_change_arrows += other.m_change_arrows;
  this->m_change_dex += other.m_change_dex;
  this->m_change_gold += other.m_change_gold;
  this->m_change_luck += other.m_change_luck;
  this->m_change_provisions += other.m_change_provisions;

  this->m_change_sta += other.m_change_sta;
  for (const auto item_to_add: other.GetItemsToAdd())
  {
    this->m_add_items.push_back(item_to_add);
  }
  for (const auto item_to_remove: other.GetItemsToRemove())
  {
    this->m_remove_items.push_back(item_to_remove);
  }

}

void Consequence::AddItemToAdd(const Item& item)
{
  m_add_items.push_back(item);
}

void Consequence::AddItemToRemove(const Item& item)
{
  m_remove_items.push_back(item);
}

void Consequence::Apply(Character& character) const
{
  #ifndef NDEBUG
  const bool verbose{false};
  #else
  const bool verbose{false};
  #endif

  if (GetNextChapter() != -1)
  {
    character.SetChapter(GetNextChapter());
  }

  //Arrows
  {
    const int change_arrows{GetChangeArrows()};
    if (change_arrows > 0)
    {
      if (verbose) { std::clog << "Changing arrows by " << change_arrows << std::endl; }
      character.ChangeArrows(change_arrows);
      const int delta_condition{-3 * change_arrows}; //Each arrow damages three condition
      if (verbose) { std::clog << "Changing condition due to arrows by " << delta_condition << std::endl; }
      character.ChangeCondition(delta_condition);
    }
    else if (change_arrows < 0)
    {
      if (verbose) { std::clog << "Changing arrows by " << character.GetArrows() << std::endl; }
      character.ChangeArrows(-character.GetArrows());
      const int delta_condition{2 * character.GetArrows()}; //Each arrow is healed by two condition
      if (verbose) { std::clog << "Changing condition due to arrows by " << delta_condition << std::endl; }
      character.ChangeCondition(delta_condition);
    }
  }
  //Dex
  {
    const int change_dex{GetChangeSkill()};
    if (change_dex != 0)
    {
      if (verbose) { std::clog << "Changing skill by " << change_dex << std::endl; }
      character.ChangeSkill(change_dex);
    }
  }
  //Gold
  {
    const int change_gold{GetChangeGold()};
    if (change_gold != 0)
    {
      if (verbose) { std::clog << "Changing gold by " << change_gold << std::endl; }
      character.ChangeGold(change_gold);
    }
  }
  //Luck
  {
    const int change_luck{GetChangeLuck()};
    if (change_luck != 0)
    {
      if (verbose) { std::clog << "Changing luck by " << change_luck << std::endl; }
      character.ChangeLuck(change_luck);
    }
  }
  //Provisions
  {
    const int change_provisions{GetChangeProvisions()};
    if (change_provisions != 0)
    {
      if (verbose) { std::clog << "Changing provisions by " << change_provisions << std::endl; }
      character.ChangeProvisions(change_provisions);
    }
  }
  //Condition
  {
    const int change_sta{GetChangeCondition()};
    if (change_sta != 0)
    {
      if (verbose) { std::clog << "Changing condition by " << change_sta << std::endl; }
      character.ChangeCondition(change_sta);
    }
  }
  for (const auto item: this->GetItemsToAdd())
  {
    if (verbose) { std::clog << "Obtained item " << ToPrettyStr(item) << std::endl; }
    character.AddItem(item);
  }
  for (const auto item: this->GetItemsToRemove())
  {
    if (item == Item::all_gold)
    {
      if (verbose) { std::clog << "Removing all gold" << std::endl; }
      character.ChangeGold(-character.GetGold());
      continue;
    }
    if (item == Item::all_provisions)
    {
      if (verbose) { std::clog << "Removing all provisions" << std::endl; }
      character.ChangeProvisions(-character.GetProvisions());
      continue;
    }
    if (item == Item::random_item_or_one_gold)
    {
      //if (verbose) { std::clog << "Removing random item or 1 gold" << std::endl; }
      auto items = character.GetItems();
      const int n_items{static_cast<int>(items.size())};
      if (n_items == 0) continue;
      if (n_items == 0 || Dice::Get()->Throw() <= 3)
      {
        if (character.GetGold() > 0)
        {
          if (verbose) { std::clog << "Removed 1 gold" << std::endl; }
          character.ChangeGold(-1);
        }
        else
        {
          //if (verbose) { std::clog << "Removing random item or 1 gold failed: character has neither" << std::endl; }
        }
      }
      else
      {
        std::shuffle(std::begin(items),std::end(items),Dice::Get()->GetEngine());
        assert(!items.empty());
        character.RemoveItem(items.back());
      }
      continue;
    }
    else if (item == Item::two_random_items)
    {
      //if (verbose) { std::clog << "Removing two random items" << std::endl; }
      for (int i=0; i!=2; ++i)
      {
        const auto items = character.GetItems();
        const int n_items{static_cast<int>(items.size())};
        if (n_items == 0) continue;
        auto iter = items.cbegin();
        const int item_index{(std::rand() >> 4) % n_items};
        for (int j=0; j!=item_index; ++j) { ++iter; }
        if (verbose) { std::clog << "Lost  " << ToPrettyStr(*iter) << std::endl; }
        character.RemoveItem(*iter);
      }
      continue;
    }
    else if (item == Item::all_silver_items)
    {
      const auto items = character.GetItems();
      for (const auto item: items)
      {
        if (IsSilver(item)) character.RemoveItem(item);
      }
      continue;
    }
    if (verbose) { std::clog << "Removed item " << ToPrettyStr(item) << std::endl; }
    character.RemoveItem(item);
  }
}

void Consequence::SetNextChapter(const int next_chapter) noexcept
{
  m_next_chapter = next_chapter;
  if (m_next_chapter < 2) { std::cerr << "WARNING: next_chapter incorrect\n"; }
  assert(m_next_chapter > 1);
}

Consequence ParseConsequence(std::stringstream &s)
{
  const Helper h;
  Consequence consequence;
  const std::string what{h.ReadString(s)};
  if (what == "add")
  {
    const std::string item_name{h.ReadString(s)};
    if (!IsItem(item_name))
    {
      std::cerr << "Unknown item: " << item_name << std::endl;
      assert(!"Should not get here");
    }
    const Item item{ToItem(item_name)};
    consequence.AddItemToAdd(item);
  }
  else if (what == "arrows" || what == "arrow")
  {
    const std::string value{h.ReadString(s)};
    if (value == "random[1-6]")
    {
      const int n_arrows{Dice::Get()->Throw()};
      consequence.SetChangeArrows(n_arrows);
    }
    else if (value == "remove_all")
    {
      consequence.SetChangeArrows(-6);
    }
    else
    {
      assert(!"Should not get here");
    }
  }
  else if (what == "skill" || what == "dexterity")
  {
    const int change_dex{h.ReadInt(s)};
    consequence.SetChangeSkill(change_dex);
  }
  else if (what == "gold")
  {
    const int change_gold{h.ReadInt(s)};
    consequence.SetChangeGold(change_gold);
  }
  else if (what == "luck")
  {
    const int change_luck{h.ReadInt(s)};
    consequence.SetChangeLuck(change_luck);
  }
  else if (what == "provision" || what == "provisions")
  {
    const int change_provisions{h.ReadInt(s)};
    consequence.SetChangeProvisions(change_provisions);
  }
  else if (what == "remove")
  {
    const std::string item_name{h.ReadString(s)};
    if (!IsItem(item_name))
    {
      std::cerr << "Unknown item: " << item_name << std::endl;
      assert(!"Should not get here");
    }
    const Item item{ToItem(item_name)};
    consequence.AddItemToRemove(item);
  }
  else if (what == "condition" || what == "stamina")
  {
    const std::string value{h.ReadString(s)};
    if (h.IsInt(value))
    {
      consequence.SetChangeCondition(h.ToInt(value));
    }
    else
    {
      assert(value == "random[1-6]");
      consequence.SetChangeCondition(Dice::Get()->Throw());
    }
  }
  else
  {
    std::cerr << "Unknown what: " << what << std::endl;
    assert(!"Should not get here");
  }
  return consequence;
}

Consequence CreateDrinkPotionConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::drink_potion);
  return c;
}

Consequence CreateEatProvisionConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::eat_provision);
  return c;
}


Consequence CreateLeaveConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::leave);
  return c;
}

Consequence CreateShowInventoryConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::show_inventory);
  return c;
}

Consequence CreateYesConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::yes);
  return c;
}

Consequence CreateNoConsequence()
{
  Consequence c;
  c.SetType(ConsequenceType::no);
  return c;
}
