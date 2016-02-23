#ifndef CONDITION_H
#define CONDITION_H

#include <iosfwd>
#include <vector>

#include "item.h"

struct Character;

///Something that is true or false
struct Condition
{
  Condition();

  ///Has the character fought this monster?
  void AddFought(const std::string& monster_name);

  ///Must have this item
  void AddItemNeeded(const Item item);

  ///Must not have this item
  void AddItemNotNeeded(const Item item);

  ///Has the character not fought this monster?
  void AddNotFought(const std::string& monster_name);

  int GetGoldNeeded() const noexcept { return m_gold_needed; }
  int GetProvisionsNeeded() const noexcept { return m_provisions_needed; }
  const std::vector<Item>& GetItemsNeeded() const noexcept { return m_items_needed; }
  const std::vector<Item>& GetItemsNotNeeded() const noexcept { return m_items_not_needed;; }

  bool IsSatisfied(const Character& character) const;

  void SetGoldNeeded(const int amount);
  void SetProvisionsNeeded(const int amount);

  private:
  ///Has the player fought these monsters?
  std::vector<std::string> m_fought;

  int m_gold_needed;
  std::vector<Item> m_items_needed;
  std::vector<Item> m_items_not_needed;

  ///Has the player not fought these monsters?
  std::vector<std::string> m_not_fought;

  int m_provisions_needed;
};

Condition ParseCondition(std::stringstream& s);
std::ostream& operator<<(std::ostream& os, const Condition& condition);

#endif // CONDITION_H
