#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "items.h"

struct Observer;

struct Character
{
  using MonsterNames = std::vector<std::string>;

  Character(
    const int skill,
    const int condition,
    const int luck,
    const Item initial_item,
    const bool auto_attack = false
  );

  Character(const Character& other);
  Character& operator=(const Character& other) = delete; //Not needed yet

  void AddHasFought(const std::string& monster_name);
  void AddItem(const Item item);

  ///In a fight, produce a random attack strength
  int CalcAttackStrength() const noexcept;

  void ChangeArrows(const int change);
  void ChangeSkill(const int change);
  void ChangeGold(const int change);
  void ChangeProvisions(const int change);
  void ChangeCondition(const int change);
  void ChangeLuck(const int change);
  void DrinkPotion();
  int GetArrows() const noexcept { return m_arrows; }
  bool GetAutoAttack() const noexcept { return m_auto_attack; }
  const std::vector<int>& GetChapters() const noexcept { return m_chapters; }
  int GetCondition() const noexcept { return m_condition; }
  int GetCurrentChapter() const noexcept { return m_chapters.back(); }
  const auto& GetFought() const noexcept { return m_fought; }
  int GetGold() const noexcept { return m_gold; }
  const Items& GetItems() const noexcept { return m_items; }
  int GetInitialSkill() const noexcept { return m_initial_skill; }
  int GetInitialLuck() const noexcept { return m_initial_luck; }
  int GetInitialCondition() const noexcept { return m_initial_condition; }
  int GetLuck() const noexcept;
  int GetLuckBase() const noexcept;
  int GetProvisions() const noexcept { return m_provisions; }
  int GetSkill() const noexcept;
  int GetSkillBase() const noexcept;
  bool HasFought(const std::string& monster_name) const noexcept;
  bool HasPotion() const noexcept;
  bool IsDead() const noexcept { return m_condition <= 0; }
  void RemoveItem(const Item item);
  void SetChapter(const int chapter);
  void SetIsDead() noexcept { m_condition = 0; }
  void SetObserver(Observer * const observer) noexcept { m_observer = observer; }
  std::string ShowInventory();
  bool TestSkill() noexcept;
  bool TestLuck() noexcept;

  private:

  ///How much arrows does the character have sticking out his/her body?
  int m_arrows;

  ///Is auto attack on?
  bool m_auto_attack;

  std::vector<int> m_chapters;
  int m_condition;
  MonsterNames m_fought;
  int m_gold;
  const int m_initial_condition;
  int m_initial_luck;
  const int m_initial_skill;
  Items m_items;
  int m_luck;

  Observer * m_observer;
  int m_provisions;
  int m_skill;

  static const bool m_verbose{false};
};

bool operator==(const Character& lhs, const Character& rhs);

/// Get the best possible character
Character GetBestCharacter(
  const Item initial_potion = Item::luck_potion,
  const bool auto_attack = true
) noexcept;

bool HasItem(const Character& c, const Item item) noexcept;

#endif // CHARACTER_H
