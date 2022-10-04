#include "walkthrough.h"

#include <cassert>
#include <iostream>

#include "game.h"
#include "helper.h"
#include "route.h"

Walkthrough::Walkthrough(
    const int seed,
    const Character& character,
    const bool silent,
    const std::vector<int>& route
) : m_game(seed,character),
    m_route{route},
    m_silent{silent}
{
  m_game.SetObserver(this);
}

int Walkthrough::GetNumberOfCharsPerLine() const noexcept
{
  return GetDefaultNumberOfCharsPerLine();
}

Character Walkthrough::Run()
{
  while (1)
  {
    m_game.DoChapter();
    if (m_game.HasWon() || m_game.HasLost()) break;
    assert(m_game.GetCharacter().GetCondition() > 0);
    assert(!IsDead(m_game.GetCharacter()));
  }
  assert(m_game.HasWon() || m_game.HasLost());
  const Character final_character{m_game.GetCharacter()};
  return final_character;
}

Option Walkthrough::RequestOption(const std::vector<Option>& options)
{
  for (const auto& option: options)
  {
    ShowText(" * " + option.GetText() + "\n");
  }
  assert(!options.empty());
  if (options.size() == 1) return options[0];
  if (options[0].GetConsequence().GetType() == ConsequenceType::no)
  {
    return options[0]; //Always say no
  }

  const int chapter_number{
    m_game.GetCurrentChapterNumber()
  };

  //Special chapters
  if (chapter_number == 52)
  {
    ///Buy all needed
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetItemsToAdd().empty()) continue;
      assert(option.GetConsequence().GetItemsToAdd().size() == 1);
      if (option.GetConsequence().GetItemsToAdd()[0] == Item::lantern)
      {
        return option;
      }
      if (option.GetConsequence().GetItemsToAdd()[0] == Item::throwing_knife)
      {
        return option;
      }
    }
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetType() == ConsequenceType::leave)
      {
        return option;
      }
    }
  }

  //Special chapters
  if (chapter_number == 354)
  {
    ///Buy all needed
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetItemsToRemove().empty()) continue;
      assert(option.GetConsequence().GetItemsToRemove().size() == 1);
      if (option.GetConsequence().GetItemsToRemove()[0] == Item::eye_patch)
      {
        return option;
      }
      if (option.GetConsequence().GetItemsToRemove()[0] == Item::silver_flute)
      {
        return option;
      }
    }
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetType() == ConsequenceType::leave)
      {
        return option;
      }
    }
  }


  if (m_route[static_cast<size_t>(chapter_number)] == 0)
  {
    std::cerr << "Do not know where to go from chapter " << chapter_number << std::endl;
  }
  assert(m_route[static_cast<size_t>(chapter_number)] != 0);
  const int target_chapter{m_route[static_cast<size_t>(chapter_number)]};
  for (const auto& option: options)
  {
    if (option.GetConsequence().GetNextChapter() == target_chapter)
    {
      return option;
    }
  }
  assert(!"Should never get here");
  return options[1];
}

void Walkthrough::ShowText(const std::string& text)
{
  if (m_silent) return;

  const std::string lines = Helper().StrToLines(text,GetNumberOfCharsPerLine());

  for (const char c: lines)
  {
    Helper().Cout(c);
  }
}

void Walkthrough::Wait()
{
  //Continue
}
