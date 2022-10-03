#ifndef MONSTER_H
#define MONSTER_H

#include <iosfwd>
#include <string>
#include <vector>

struct Monster
{
  Monster(
    const std::string& name,
    const int skill,
    const int condition,
    const int attack_damage = 2,
    const bool has_fire_breath = false
  );

  ///In a fight, produce a random attack strength
  int CalcAttackStrength() const noexcept;

  void ChangeCondition(const int delta_condition) noexcept;

  ///If the monster hits the player, how much damage will be dealt. This dependends on the weapon
  int GetAttackDamage() const noexcept { return m_attack_damage; }

  int GetSkill() const noexcept { return m_skill; }

  bool HasFireBreath() const noexcept { return m_has_fire_breath; }

  int GetInitialCondition() const noexcept { return m_initial_condition; }
  std::string GetName() const noexcept { return m_name; }
  int GetCondition() const noexcept { return m_condition; }
  bool IsDead() const noexcept { return m_condition < 1; }

  private:
  const int m_attack_damage;
  const int m_skill;
  const bool m_has_fire_breath;
  const int m_initial_condition;
  const std::string m_name;
  int m_condition;
};

///@seealso logistic function to call ToStr
std::string MonstersToStr(const std::vector<Monster>& ms) noexcept;

Monster ParseMonster(std::stringstream& s);
std::vector<Monster> ParseMonsters(std::stringstream& s);


std::string ToStr(const Monster& m) noexcept;
std::string ToStr(const std::vector<Monster>& ms) noexcept;
std::ostream& operator<<(std::ostream& os, const Monster& monster) noexcept;
std::ostream& operator<<(std::ostream& os, const std::vector<Monster>& monsters) noexcept;

#endif // MONSTER_H
