#include "option.h"

#include <cassert>
#include <iostream>

Option::Option(
  const std::string& text,
  const Consequence& consequence
)
  : m_condition{},
    m_consequence{consequence},
    m_text{text}
{
  assert(!text.empty());
  if (GetNextChapter() == 1)
  {
    std::cerr << "WARNING: next chapter is 1" << std::endl;
    assert(!"Should not get here");
  }
}

bool Option::CanChoose(const Character& character) const
{
  return m_condition.IsSatisfied(character);
}

void Option::DoChoose(Character& character) const
{
  assert(CanChoose(character));
  GetConsequence().Apply(character);
}

void Option::SetCondition(const Condition& condition)
{
  m_condition = condition;
}

std::ostream& operator<<(std::ostream& os, const Option& option)
{
  os
    << "Condition: " << option.GetCondition() << '\n'
    << "m_next_chapter: " << option.GetNextChapter() << '\n'
    << "m_text: " << option.GetText() << '\n'
  ;
  return os;
}

std::vector<Option> CreateInitialPotionOptions()
{
  std::vector<Option> options;
  {
    Consequence consequence;
    consequence.AddItemToAdd(Item::stamina_potion);
    Option option("Stamina potion",consequence);
    options.push_back(option);
  }
  {
    Consequence consequence;
    consequence.AddItemToAdd(Item::dexterity_potion);
    Option option("Dexterity potion",consequence);
    options.push_back(option);
  }
  {
    Consequence consequence;
    consequence.AddItemToAdd(Item::luck_potion);
    Option option("Luck potion",consequence);
    options.push_back(option);
  }
  return options;
}

Option CreateDrinkPotionOption()
{
  Option option("Drink potion",CreateDrinkPotionConsequence());
  return option;
}

Option CreateEatProvisionOption()
{
  Option option("Eat provision",CreateEatProvisionConsequence());
  return option;
}


Option CreateLeaveOption()
{
  Option option("Leave",CreateLeaveConsequence());
  return option;
}

Option CreateShowInventoryOption()
{
  Option option("Inventory",CreateShowInventoryConsequence());
  return option;
}

Option CreateYesOption()
{
  Option option("Yes",CreateYesConsequence());
  return option;
}

Option CreateNoOption()
{
  Option option("No",CreateNoConsequence());
  return option;
}


std::vector<Option> CreateYesNoOptions()
{
  std::vector<Option> options;
  options.push_back(CreateNoOption());
  options.push_back(CreateYesOption());
  return options;
}
