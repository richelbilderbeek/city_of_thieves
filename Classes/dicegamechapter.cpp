#include "dicegamechapter.h"

#include "chapter.h"
#include "character.h"
#include "dice.h"
#include "helper.h"

DiceGameChapter::DiceGameChapter(Chapter& chapter)
  : m_chapter{chapter}
{

}

void DiceGameChapter::Do(Character& character) const
{
  const Helper h;
  if (character.GetGold() < 2)
  {
    m_chapter.ShowText("You cannot afford to play this game.\n");
    return;
  }

  m_chapter.ShowText("Do you want to play?\n");
  {
    const auto options = CreateYesNoOptions();
    const auto chosen = m_chapter.RequestOption(options);
    if (chosen.GetConsequence().GetType() == ConsequenceType::no) { return; }
  }

  const int n_rounds{4};
  for (int round = 0; round != 4; ++round)
  {
    m_chapter.ShowText("Round #" + h.ToStr(round + 1) + "/" + h.ToStr(n_rounds) + "\n");
    //You
    const int dice_you{Dice::Get()->Throw()};
    const int dice_1{Dice::Get()->Throw()};
    const int dice_2{Dice::Get()->Throw()};
    const int dice_3{Dice::Get()->Throw()};
    m_chapter.ShowText("You throw: " + h.ToStr(dice_you) + "\n");
    m_chapter.Wait();
    m_chapter.ShowText("Dwarf 1 throws: " + h.ToStr(dice_1) + "\n");
    m_chapter.Wait();
    m_chapter.ShowText("Dwarf 2 throws: " + h.ToStr(dice_2) + "\n");
    m_chapter.Wait();
    m_chapter.ShowText("Dwarf 3 throws: " + h.ToStr(dice_3) + "\n");
    m_chapter.Wait();
    if (dice_you > dice_1 && dice_you > dice_2 && dice_you > dice_3)
    {
      m_chapter.ShowText("You won! You collect your 6 gold pieces from the three dwarves.\n");
      character.ChangeGold(6);
      m_chapter.Wait();
    }
    else if (dice_you < dice_1 || dice_you < dice_2 || dice_you < dice_3)
    {
      m_chapter.ShowText("You Lost! You lose 2 gold pieces to the three dwarves.\n");
      character.ChangeGold(-2);
      m_chapter.Wait();
    }
    else
    {
      m_chapter.ShowText("A draw. You keep your gold\n");
      m_chapter.Wait();
    }

    if (character.GetGold() < 2)
    {
      m_chapter.ShowText("You cannot afford to play another round.\n");
      break;
    }

    if (round == 3) break;

    //Play again?
    {
      m_chapter.ShowText("Do you want to play another round?\n");
      const auto options = CreateYesNoOptions();
      const auto chosen = m_chapter.RequestOption(options);
      if (chosen.GetConsequence().GetType() == ConsequenceType::no) { return; }
    }
  }
}
