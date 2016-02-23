#ifndef OPTION_H
#define OPTION_H

#include <iosfwd>
#include <string>
#include <vector>

#include "condition.h"
#include "consequence.h"

struct Character;

///An option the player may or may not choose
///Option [text]@ goto [chapter]@
///Option [text]@ if [conditionals] goto [chapter]@
///Option [text]@ then [consequences] goto [chapter]@
///Option [text]@ if [conditionals] change [consequences] goto [chapter]@
struct Option
{
  Option(
    const std::string& text,
    const Consequence& consequence
  );

  bool CanChoose(const Character& character) const;

  void DoChoose(Character& character) const;

  const Condition& GetCondition() const noexcept { return m_condition; }

  const Consequence& GetConsequence() const noexcept { return m_consequence; }

  int GetNextChapter() const noexcept { return m_consequence.GetNextChapter(); }

  const std::string& GetText() const noexcept { return m_text; }

  void SetCondition(const Condition& condition);


  private:
  Condition m_condition;
  Consequence m_consequence;
  std::string m_text;
};

std::ostream& operator<<(std::ostream& os, const Option& option);

Option CreateDrinkPotionOption();
Option CreateEatProvisionOption();
Option CreateLeaveOption();
Option CreateNoOption();
Option CreateShowInventoryOption();
Option CreateYesOption();
std::vector<Option> CreateInitialPotionOptions();
std::vector<Option> CreateYesNoOptions();

#endif // OPTION_H
