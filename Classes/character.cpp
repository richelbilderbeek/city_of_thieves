#include "character.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <sstream>
#include <iterator>
#include <fstream>

#include "dice.h"
#include "helper.h"
#include "observer.h"
#include "skill.h"
#include "luck.h"
#include "playercondition.h"

Character::Character(const Character& other)
  :
    m_arrows{other.m_arrows},
    m_auto_attack{other.m_auto_attack},
    m_chapters{other.m_chapters},
    m_condition{other.m_condition},
    m_fought{other.m_fought},
    m_gold{other.m_gold},
    m_initial_condition{other.m_initial_condition},
    m_initial_luck{other.m_initial_luck},
    m_initial_skill{other.m_initial_skill},
    m_items{other.m_items},
    m_luck{other.m_luck},
    m_observer{nullptr},
    m_provisions{other.m_provisions},
    m_skill{other.m_skill}
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
}


Character::Character(
  const int skill,
  const int condition,
  const int luck,
  const Item initial_item,
  const bool auto_attack
)
  :
    m_arrows{0},
    m_auto_attack{auto_attack},
    m_chapters{std::vector<int>(1,1)},
    m_condition{condition},
    m_fought{},
    m_gold{30},
    m_initial_condition{condition},
    m_initial_luck{luck},
    m_initial_skill{skill},
    m_items{},
    m_luck{luck},
    m_observer{nullptr},
    m_provisions{10},
    m_skill{skill}
{
  m_items.push_back(Item::shield);
  m_items.push_back(Item::carralifs_sword);
  assert(
    initial_item == Item::dexterity_potion
    || initial_item == Item::luck_potion
    || initial_item == Item::stamina_potion
  );
  m_items.push_back(initial_item);
}

void Character::AddHasFought(const std::string& monster_name)
{
  assert(!HasFought(monster_name));
  m_fought.push_back(monster_name);
  m_observer->CharacterChanged(*this);
}

void Character::AddItem(const Item item)
{
  if (HasItem(*this, item))
  {
    #ifndef NDEBUG
    std::cerr << "WARNING: adding item " << item << " for the second time!" << std::endl;
    std::cerr << ShowInventory() << std::endl;
    #endif
    assert(!"Should not get here");
  }
  m_items.push_back(item);
  if (m_observer) { m_observer->CharacterChanged(*this); }

}

int Character::CalcAttackStrength() const noexcept
{
  int shield_value = 0;
  if (HasItem(*this, Item::shield_with_tower_crest)) { shield_value = 0; } //Cursed
  else if (HasItem(*this, Item::shield_with_unicorn_crest)) { shield_value = 1; }
  else if (HasItem(*this, Item::magnificent_shield)) { shield_value = 1; }
  else if (HasItem(*this, Item::shield)) { shield_value = 0; }

  return GetSkill()
    + (HasItem(*this, Item::magic_helmet) ? 1 : 0)
    + shield_value
    + (Dice::Get()->Throw())
    + (Dice::Get()->Throw())
  ;
}

void Character::ChangeArrows(const int change)
{
  m_arrows += change;
  if (m_arrows < 0)
  {
    std::cerr << "WARNING: Character's number of arrows in his/her body is negative" << std::endl;
    assert(m_arrows >= 0);
  }
  if (change != 0)
  {
    m_observer->CharacterChanged(*this);

  }
}


void Character::ChangeSkill(const int change)
{
  const int skill_before{m_skill};
  m_skill += change;
  m_skill = std::min(m_skill,m_initial_skill);
  const int skill_after{m_skill};
  if (skill_before != skill_after)
  {
    m_observer->CharacterChanged(*this);

  }
}

void Character::ChangeGold(const int change)
{
  m_gold += change;
  if (m_gold < 0)
  {
    #ifndef NDEBUG
    //std::cerr << "WARNING: Character's gold became negative, set to zero instead" << std::endl;
    #endif
    m_gold = 0;
    //assert(m_gold >= 0);
  }
  if (change != 0 && m_observer)
  {
    m_observer->CharacterChanged(*this);

  }
}

void Character::ChangeProvisions(const int change)
{
  m_provisions += change;
  assert(m_provisions >= 0);
  if (change != 0 && m_observer)
  {
    m_observer->CharacterChanged(*this);

  }
}

void Character::ChangeCondition(const int change)
{
  const int condition_before{m_condition};
  m_condition += change;
  m_condition = std::min(m_condition,m_initial_condition);
  if (m_condition < 0)
  {
    m_condition = 0;
    this->SetIsDead();
  }
  const int condition_after{m_condition};
  if (condition_before != condition_after && m_observer)
  {
    m_observer->CharacterChanged(*this);

  }
}

void Character::ChangeLuck(const int change)
{
  const int luck_before{m_luck};
  m_luck += change;
  m_luck = std::min(m_luck,m_initial_luck);
  const int luck_after{m_luck};
  if (luck_before != luck_after && m_observer)
  {
    m_observer->CharacterChanged(*this);

  }
}

void Character::DrinkPotion()
{
  assert(HasPotion());
  if (HasItem(*this, Item::dexterity_potion))
  {
    m_skill = m_initial_skill;
    RemoveItem(Item::dexterity_potion);
  }
  else if (HasItem(*this, Item::stamina_potion))
  {
    m_condition = m_initial_condition;
    RemoveItem(Item::stamina_potion);
  }
  else if (HasItem(*this, Item::luck_potion))
  {
    ++m_initial_luck;
    m_luck = m_initial_luck;
    RemoveItem(Item::luck_potion);
  }
  else
  {
    assert(!"Should not get here");
  }
}

Character GetBestCharacter(
  const Item initial_potion,
  const bool auto_attack
) noexcept
{
  const int skill{GetBestInitialSkill()};
  const int condition{GetBestInitialCondition()};
  const int luck{GetBestInitialLuck()};
  return Character(
    skill, condition, luck,
    initial_potion, auto_attack
  );
}

int Character::GetSkill() const noexcept
{
  int shield_value = 0;
  if (HasItem(*this, Item::shield_with_tower_crest)) { shield_value = -1; } //Cursed
  else if (HasItem(*this, Item::shield_with_unicorn_crest)) { shield_value = 3; }
  else if (HasItem(*this, Item::magnificent_shield)) { shield_value = 2; }
  else if (HasItem(*this, Item::shield)) { shield_value = 1; }


  int sword_value = 0;
  if (HasItem(*this, Item::ordinary_sword)) { sword_value = 1; }
  else if (HasItem(*this, Item::carralifs_sword)) { sword_value = 2; }

  return
    GetSkillBase()
    + (HasItem(*this, Item::cursed_white_silk_glove) ? -2 : 0)
    + (HasItem(*this, Item::magic_elven_boots) ? 1 : 0)
    + shield_value
    + (HasItem(*this, Item::chainmail_coat) ? 2 : 0)
    + sword_value
  ;
}

int Character::GetSkillBase() const noexcept
{
  return m_skill;
}

int Character::GetLuck() const noexcept
{
  return
    GetLuckBase()
    + (HasItem(*this, Item::copper_scorpion_brooch) ? -1 : 0)
    + (HasItem(*this, Item::golden_scorpion_brooch) ? 2 : 0)
  ;
}

int Character::GetLuckBase() const noexcept
{
  return m_luck;
}

bool Character::HasFought(const std::string& monster_name) const noexcept
{
  return std::count(
    std::begin(m_fought),
    std::end(m_fought),
    monster_name
  ) > 0;
}

/*
bool Character::HasItem(const Item item) const
{
  const int n{static_cast<int>(
      std::count(std::begin(m_items),std::end(m_items),item)
    )
  };
  assert(n == 0 || n == 1);
  return n;
}
*/

bool HasItem(const Character& c, const Item item) noexcept
{
  const auto& items{c.GetItems()};
  const int n{static_cast<int>(
      std::count(std::begin(items),std::end(items),item)
    )
  };
  assert(n == 0 || n == 1);
  return n;
}


bool Character::HasPotion() const noexcept
{
  return HasItem(*this, Item::stamina_potion)
    || HasItem(*this, Item::dexterity_potion)
    || HasItem(*this, Item::luck_potion)
  ;
}

bool IsDead(const Character& c) noexcept
{
  return c.GetCondition() <= 0;
}

void Character::RemoveItem(Item item)
{
  if (m_items.empty()) return;
  if (item == Item::two_random_items)
  {
    auto items = m_items;
    if (items.empty()) { return; }
    std::shuffle(std::begin(items),std::end(items),Dice::Get()->GetEngine());
    RemoveItem(items.front());
    if (items.empty()) { return; }
    std::shuffle(std::begin(items),std::end(items),Dice::Get()->GetEngine());
    RemoveItem(items.front());
  }
  else if (item == Item::all_silver_items)
  {
    const auto silver_items = {
      Item::silver_arrow,
      Item::silver_chalice,
      Item::silver_flute,
      Item::silver_insect_bracelet,
      Item::silver_scorpion_brooch,
      Item::silver_spoon
    };
    for (const auto& silver_item: silver_items)
    {
      if (HasItem(*this, silver_item)) RemoveItem(silver_item);
    }
    return;
  }

  const auto iter = std::find(std::begin(m_items),std::end(m_items),item);
  if (iter == std::end(m_items))
  {
    std::stringstream error;
    error << "Attempted to remove item " << ToStr(item) << " which is not possessed\n";
    std::cerr << error.str();
    assert(!"Should not get here");
  }
  assert(iter != std::end(m_items));
  std::swap(*iter,m_items.back());
  m_items.pop_back();

  if (m_observer) { m_observer->CharacterChanged(*this); }

}

void Character::SetChapter(const int chapter)
{
  if (chapter == -1)
  {
    std::cerr << "ERROR: cannot go to chapter -1" << std::endl;
    assert(!"Should not get here");
  }
  if (
    std::find(std::begin(m_chapters),std::end(m_chapters),chapter) != std::end(m_chapters)
  )
  {
    //These chapters can be legally visited more often
    if (
         chapter != 96
      && chapter != 65
      && chapter != 122
      && chapter != 197
      && chapter != 231
      && chapter != 232
      && chapter != 234
      && chapter != 284
      && chapter != 314
      && chapter != 319
      && chapter != 383
    )
    {
      #ifndef NDEBUG
      std::cerr << "WARNING: entering chapter " << chapter << " for the second time!" << std::endl;
      std::cerr << ShowInventory() << std::endl;
      #endif
      const auto v = GetChapters();
      std::cerr << "Path taken: ";
      std::copy(std::begin(v),std::end(v),std::ostream_iterator<int>(std::cerr," "));
      std::cerr << std::endl;
      assert(!"Should not get here");
    }
  }

  //assert(std::find(std::begin(m_chapters),std::end(m_chapters),chapter) == std::end(m_chapters));
  m_chapters.push_back(chapter);
  m_observer->CharacterChanged(*this);

}

std::string Character::ShowInventory()
{
  std::stringstream s;
  s
    << "skill:\n"
    << " * base: " << GetSkillBase() << "/" << GetInitialSkill() << '\n'
  ;

  //Shield
  if (HasItem(*this, Item::shield_with_tower_crest))
  {
    s << " * " << ToPrettyStr(Item::shield_with_tower_crest) << ": -1 (equipped, cursed)\n";

    if (HasItem(*this, Item::shield_with_unicorn_crest)) { s << " * " << ToPrettyStr(Item::shield_with_unicorn_crest) << ": +3\n"; }
    if (HasItem(*this, Item::magnificent_shield)) { s << " * " << ToPrettyStr(Item::magnificent_shield) << ": +2\n"; }
    if (HasItem(*this, Item::shield)) { s << " * " << ToPrettyStr(Item::shield) << ": +1\n"; }
  }
  else if (HasItem(*this, Item::shield_with_unicorn_crest))
  {
    s << " * " << ToPrettyStr(Item::shield_with_unicorn_crest) << ": +3 (equipped)\n";
    if (HasItem(*this, Item::magnificent_shield)) { s << " * " << ToPrettyStr(Item::magnificent_shield) << ": +2\n"; }
    if (HasItem(*this, Item::shield)) { s << " * " << ToPrettyStr(Item::shield) << ": +1\n"; }
  }
  else if (HasItem(*this, Item::magnificent_shield))
  {
    if (HasItem(*this, Item::magnificent_shield)) { s << " * " << ToPrettyStr(Item::magnificent_shield) << ": +2 (equipped)\n"; }
    if (HasItem(*this, Item::shield)) { s << " * " << ToPrettyStr(Item::shield) << ": +1\n"; }
  }
  else if (HasItem(*this, Item::shield))
  {
    if (HasItem(*this, Item::shield)) { s << " * " << ToPrettyStr(Item::shield) << ": +1 (equipped)\n"; }
  }

  //Sword
  if (HasItem(*this, Item::carralifs_sword))
  {
    s << " * " << ToPrettyStr(Item::carralifs_sword) << ": +2 (equipped) \n";
    if (HasItem(*this, Item::ordinary_sword)) { s << " * " << ToPrettyStr(Item::ordinary_sword) << ": +1\n"; }
  }
  else if (HasItem(*this, Item::ordinary_sword))
  {
    if (HasItem(*this, Item::ordinary_sword)) { s << " * " << ToPrettyStr(Item::ordinary_sword) << ": +1 (equipped)\n"; }
  }

  //Boots
  if (HasItem(*this, Item::magic_elven_boots)) { s << " * " << ToPrettyStr(Item::magic_elven_boots) << ": +1 (equipped)\n"; }

  //Chainmail coat
  if (HasItem(*this, Item::chainmail_coat)) { s << " * " << ToPrettyStr(Item::chainmail_coat) << ": +2 (equipped)\n"; }

  //Cursed gloves
  if (HasItem(*this, Item::cursed_white_silk_glove)) { s << " * " << ToPrettyStr(Item::cursed_white_silk_glove) << ": -2 (equipped, cursed)\n"; }

  s
    << " * total: " << GetSkill() << "/" << GetInitialSkill() << '\n'
    << "condition: " << GetCondition() << "/" << GetInitialCondition() << '\n'
    << "luck:\n"
    << " * base: " << GetLuckBase() << "/" << GetInitialLuck() << '\n'
  ;
  if (HasItem(*this, Item::golden_scorpion_brooch)) { s << " * " << ToPrettyStr(Item::golden_scorpion_brooch) << ": +2\n"; }
  //Note: the copper brooch decreases luck with 1, but this is not shown on purpose
  //I cannot avoid that it will be easy to see that base luck and total luck don't match
  s
    << " * total: " << GetLuck() << "/" << GetInitialLuck() << '\n'
    << "gold pieces: " << GetGold() << '\n'
    << "provisions: " << GetProvisions() << '\n'
    << '\n'
  ;

  if (GetArrows() != 0)
  {
    s << "You got " << GetArrows() << " arrows sticking in your body\n";
  }

  s << "items: \n";
  for (const Item item: GetItems())
  {
    if (static_cast<int>(item) < 70) //Only concrete objects
    {
      s << " * " << ToPrettyStr(item) << '\n';
    }
  }

  s << "monsters fought: \n";
  for (const auto& monster_name: m_fought)
  {
    s << " * " << Helper().ToPretty(monster_name) << '\n';
  }
  if (m_fought.empty())
  {
    s << " * (none yet)\n";
  }

  return s.str();
}

bool Character::TestSkill() noexcept
{
  const int dice{
      Dice::Get()->Throw()
    + Dice::Get()->Throw()
  };
  return dice < GetSkill();
}

bool Character::TestLuck() noexcept
{
  const int dice{
      Dice::Get()->Throw()
    + Dice::Get()->Throw()
  };
  const bool has_luck{dice < GetLuck()};
  --m_luck;
  m_observer->CharacterChanged(*this);

  return has_luck;
}

bool operator==(const Character& lhs, const Character& rhs)
{
  return
       lhs.GetChapters() == rhs.GetChapters()
    && lhs.GetArrows() == rhs.GetArrows()
    && lhs.GetSkill() ==  rhs.GetSkill()
    && lhs.GetFought() == rhs.GetFought()
    && lhs.GetGold() == rhs.GetGold()
    && lhs.GetInitialSkill() == rhs.GetInitialSkill()
    && lhs.GetInitialLuck() && rhs.GetInitialLuck()
    && lhs.GetInitialCondition() == rhs.GetInitialCondition()
    && lhs.GetItems() == rhs.GetItems()
    && lhs.GetLuck() == rhs.GetLuck()
    && lhs.GetProvisions() == rhs.GetProvisions()
    && lhs.GetCondition() == rhs.GetCondition()
  ;
}
