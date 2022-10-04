#ifndef CONSEQUENCE_H
#define CONSEQUENCE_H

#include <iosfwd>
#include <vector>

#include "consequencetype.h"
#include "items.h"

struct Character;

struct Consequence
{
  Consequence();

  ///Add the other's consequences to this one
  void Add(const Consequence& other);

  void AddItemToAdd(const Item& item);
  void AddItemToRemove(const Item& item);

  ///Let the character have/suffer the consequences
  void Apply(Character& character) const;

  ///Which items are added to the player's inventory?
  const Items& GetItemsToAdd() const noexcept { return m_add_items; }

  ///Which items are removed to the player's inventory?
  const Items& GetItemsToRemove() const noexcept { return m_remove_items; }

  ///How much will the number of arrows in the character his/her body change?
  int GetChangeArrows() const noexcept { return m_change_arrows; }

  ///How will the skill of the character change in this chapter?
  int GetChangeSkill() const noexcept { return m_change_dex; }

  ///How will the gold of the character change in this chapter?
  int GetChangeGold() const noexcept { return m_change_gold; }

  ///How will the luck of the character change in this chapter?
  int GetChangeLuck() const noexcept { return m_change_luck; }

  ///How will the provisions of the character change in this chapter?
  int GetChangeProvisions() const noexcept { return m_change_provisions; }

  ///How will the condition of the character change in this chapter?
  int GetChangeCondition() const noexcept { return m_change_sta; }

  int GetNextChapter() const noexcept { return m_next_chapter; }

  ConsequenceType GetType() const noexcept { return m_type; }

  void SetChangeArrows(const int n_arrows) noexcept { m_change_arrows = n_arrows; }
  void SetChangeSkill(const int dex) noexcept { m_change_dex = dex; }
  void SetChangeGold(const int gold) noexcept { m_change_gold = gold; }
  void SetChangeLuck(const int luck) noexcept { m_change_luck = luck; }
  void SetChangeProvisions(const int n_provisions) noexcept { m_change_provisions = n_provisions; }
  void SetChangeCondition(const int sta) noexcept { m_change_sta = sta; }

  void SetNextChapter(const int next_chapter) noexcept;
  void SetType(const ConsequenceType type) noexcept { m_type = type; }

  private:

  ///Which items are added to the player's inventory?
  Items m_add_items;

  ///How much will the number of arrows in the character his/her body change?
  int m_change_arrows;

  ///How much will the skill of the character change?
  int m_change_dex;

  ///How much will the gold of the character change?
  int m_change_gold;

  ///How much will the luck of the character change?
  int m_change_luck;

  ///How much will the provisions of the character change?
  int m_change_provisions;

  ///How much will the condition of the character change?
  int m_change_sta;

  ///What will the next chapter be?
  int m_next_chapter;

  ///Which items are removed to the player's inventory?
  Items m_remove_items;

  ConsequenceType m_type;
};

Consequence CreateDrinkPotionConsequence();
Consequence CreateEatProvisionConsequence();
Consequence CreateLeaveConsequence();
Consequence CreateNoConsequence();
Consequence CreateShowInventoryConsequence();
Consequence CreateYesConsequence();

/// Is the consequence empty, i.e. there is no effect?
bool IsNoConsequence(const Consequence& c) noexcept;

Consequence ParseConsequence(std::stringstream& s);

bool operator==(const Consequence& lhs, const Consequence& rhs) noexcept;



#endif // CONSEQUENCE_H
