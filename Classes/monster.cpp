#include "monster.h"

#include <cassert>
#include <iostream>

#include "dice.h"
#include "helper.h"

Monster::Monster(
  const std::string& name,
  const int skill,
  const int condition,
  const int attack_damage,
  const bool has_fire_breath
)
  : m_attack_damage{attack_damage},
    m_skill{skill},
    m_has_fire_breath{has_fire_breath},
    m_initial_condition{condition},
    m_name{name},
    m_condition{condition}
{
  assert(!name.empty());
  assert(skill > 0);
  assert(condition > 0);
  assert(!IsDead());
}

void Monster::ChangeCondition(const int delta_condition) noexcept
{
  assert(!IsDead());
  m_condition += delta_condition;
}

int Monster::CalcAttackStrength() const noexcept
{
  return m_skill
    + Dice::Get()->Throw()
    + Dice::Get()->Throw()
  ;
}

Monster ParseMonster(std::stringstream& s)
{
  const Helper h;
  const std::string name{h.ReadString(s)};
  const int skill{h.ReadInt(s)};
  const int condition{h.ReadInt(s)};
  const std::string attack{h.ReadString(s)};
  int attack_strength{2};
  bool has_fire_breath{false};
  if (h.IsInt(attack))
  {
    attack_strength = h.ToInt(attack);
  }
  else
  {
    assert(attack == "2+fire");
    has_fire_breath = true;
  }
  const Monster monster(name,skill,condition,attack_strength,has_fire_breath);
  return monster;
}

std::vector<Monster> ParseMonsters(std::stringstream& s)
{
  std::vector<Monster> monsters;
  while (1)
  {
    const std::string what{Helper().ReadString(s)};
    if (what == "@") break;
    assert(what == "monster");
    const Monster monster{ParseMonster(s)};
    monsters.push_back(monster);
  }
  return monsters;
}

std::ostream& operator<<(std::ostream& os, const Monster& monster)
{
  os << monster.GetName() << " "
     << monster.GetSkill() << " "
     << monster.GetCondition() << " "
     << monster.GetAttackDamage()
  ;
  return os;
}
