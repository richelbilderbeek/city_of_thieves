#include "condition.h"

#include <algorithm>
#include <cassert>
#include <iostream>

#include "character.h"
#include "helper.h"

Condition::Condition()
  : m_fought{},
    m_gold_needed{0},
    m_items_needed{},
    m_items_not_needed{},
    m_not_fought{},
    m_provisions_needed{0}
{

}

void Condition::AddFought(const std::string& monster_name)
{
  m_fought.push_back(monster_name);
}

void Condition::AddItemNeeded(const Item item)
{
  assert(
    std::count(
      std::begin(m_items_needed),
      std::end(m_items_needed),
      item
    ) == 0
  );
  m_items_needed.push_back(item);
}

void Condition::AddItemNotNeeded(const Item item)
{
  assert(
    std::count(
      std::begin(m_items_not_needed),
      std::end(m_items_not_needed),
      item
    ) == 0
  );
  m_items_not_needed.push_back(item);
}

void Condition::AddNotFought(const std::string& monster_name)
{
  m_not_fought.push_back(monster_name);
}

bool Condition::IsSatisfied(const Character &character) const
{
  if (GetGoldNeeded() > character.GetGold()) return false;
  if (GetProvisionsNeeded() > character.GetProvisions()) return false;

  for (const auto monster_name: m_fought)
  {
    if (!character.HasFought(monster_name)) return false;
  }

  for (const auto monster_name: m_not_fought)
  {
    if (character.HasFought(monster_name)) return false;
  }

  for (const auto item_needed: GetItemsNeeded())
  {
    if (item_needed == Item::all_needed_to_slay_zanbar_bone)
    {
      if ( !character.HasItem(Item::tattoo)
        || !character.HasItem(Item::lotus_flower)
        || !character.HasItem(Item::black_pearls)
        || !character.HasItem(Item::hags_hair)
        || !character.HasItem(Item::silver_arrow)
      )
      {
        return false;
      }
    }
    else if (item_needed == Item::any_scorpion_brooch)
    {
      if ( !character.HasItem(Item::copper_scorpion_brooch)
        && !character.HasItem(Item::silver_scorpion_brooch)
        && !character.HasItem(Item::golden_scorpion_brooch)
      ) return false;
    }
    else
    {
      if (!character.HasItem(item_needed)) return false;
    }
  }
  for (const auto item_not_needed: GetItemsNotNeeded())
  {
    if (item_not_needed == Item::any_scorpion_brooch)
    {
      if ( character.HasItem(Item::copper_scorpion_brooch)
        || character.HasItem(Item::silver_scorpion_brooch)
        || character.HasItem(Item::golden_scorpion_brooch)
      ) return false;
    }
    else if (item_not_needed == Item::all_needed_to_slay_zanbar_bone)
    {
      if ( character.HasItem(Item::tattoo)
        && character.HasItem(Item::lotus_flower)
        && character.HasItem(Item::black_pearls)
        && character.HasItem(Item::hags_hair)
        && character.HasItem(Item::silver_arrow)
      )
      {
        return false;
      }
    }
    else
    {
      if (character.HasItem(item_not_needed)) return false;
    }
  }
  return true;
}

void Condition::SetGoldNeeded(const int gold_needed)
{
  assert(gold_needed > 0);
  m_gold_needed = gold_needed;
}

void Condition::SetProvisionsNeeded(const int provisions_needed)
{
  assert(provisions_needed > 0);
  m_provisions_needed = provisions_needed;
}

Condition ParseCondition(std::stringstream& s)
{
  const Helper h;
  Condition condition;
  const std::string what{h.ReadString(s)};

  if (what.empty())
  {
    assert(!"Should not get here");
  }
  else if (what == "fought" || what == "has_fought")
  {
    const std::string monster_name{h.ReadString(s)};
    condition.AddFought(monster_name);
  }
  else if (what == "gold")
  {
    const int gold_amount{h.ReadInt(s)};
    condition.SetGoldNeeded(gold_amount);
  }
  else if (what == "has")
  {
    const std::string item{h.ReadString(s)};
    if (!IsItem(item))
    {
      std::cerr << "Unknown item " << item << std::endl;
      assert(!"Should not get here");
    }
    const Item item_needed{ToItem(item)};
    condition.AddItemNeeded(item_needed);
  }
  else if (what == "has_not" || what == "hasnot")
  {
    const std::string item{h.ReadString(s)};
    if (!IsItem(item))
    {
      std::cerr << "Unknown item " << item << std::endl;
      assert(!"Should not get here");
    }
    const Item item_not_needed{ToItem(item)};
    condition.AddItemNotNeeded(item_not_needed);
  }
  else if (IsItem(what)) //assumes item is needed, 'has' before it can be omitted
  {
    const Item item_needed{ToItem(what)};
    condition.AddItemNeeded(item_needed);
  }
  else if (what == "not_fought" || what == "has_not_fought")
  {
    const std::string monster_name{h.ReadString(s)};
    condition.AddNotFought(monster_name);
  }
  else if (what == "provisions" || what == "provision")
  {
    const int number_of_provisions{h.ReadInt(s)};
    condition.SetProvisionsNeeded(number_of_provisions);
  }
  else
  {
    std::cerr << "Unknown option after if: " << what << std::endl;
    assert(!"Should not get here");
  }
  return condition;
}

std::ostream& operator<<(std::ostream& os, const Condition& condition)
{
  os
    << "gold needed: " << condition.GetGoldNeeded()
    << ", items needed: {"
  ;
  for (const auto item: condition.GetItemsNeeded())
  {
    os << ToStr(item) << ", ";
  }
  os << "}, items not_needed: {";
  for (const auto item: condition.GetItemsNotNeeded())
  {
    os << ToStr(item) << ", ";
  }
  os << "}";
  return os;
}
