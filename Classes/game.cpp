#include "game.h"

#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>

#include "ai.h"
#include "character.h"
#include "terminal.h"
#include "dice.h"
#include "helper.h"
#include "chapter.h"
#include "walkthrough.h"

Game::Game(
  const int rng_seed,
  const Character& character
)
  :
    m_character{character},
    m_has_lost{false},
    m_has_won{false},
    m_observer{nullptr}

{
  if (m_verbose) { std::clog << __func__ << std::endl; }

  #ifndef NDEBUG
  Test();
  #endif
  Dice::Get()->SetSeed(rng_seed);
}

void Game::DoChapter()
{
  if (m_has_lost || m_has_won) return;

  const int chapter_number{GetCurrentChapterNumber()};

  const Chapter chapter(chapter_number);
  chapter.SetObserver(m_observer);

  chapter.Do(m_character);

  if (m_character.IsDead()) { m_has_lost = true; }
  if (chapter_number == 400) { m_has_won = true; }
}

int Game::GetCurrentChapterNumber() const noexcept
{
  return m_character.GetCurrentChapter();
}

#ifndef NDEBUG
void Game::SetChapter(const int chapter)
{
  this->m_character.SetChapter(chapter);
}
#endif

void Game::SlotCharacterChanged(const Character& character)
{
  assert(m_observer);
  m_observer->CharacterChanged(character);
}

Option Game::SlotRequestOption(const std::vector<Option>& valid_options)
{
  assert(m_observer);
  return m_observer->RequestOption(valid_options);
}

void Game::SlotShowText(const std::string& text)
{
  assert(m_observer);
  m_observer->ShowText(text);
}

void Game::SlotWait()
{
  assert(m_observer);
  m_observer->Wait();
}

#ifndef NDEBUG
void Game::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }
  const bool verbose{false};
  if (verbose) { std::clog << __func__ << std::endl; }

  {
    Helper();
  }


  if (verbose) { std::clog << "Create a chapter" << std::endl; }
  {
    Chapter(1);
  }
  if (verbose) { std::clog << "Test if game runs identically twice with same RNG seed" << std::endl; }
  {
    const int seed{123456};
    Dice::Get()->SetSeed(seed);

    Character character1(
      Dice::Get()->Throw(),
      Dice::Get()->Throw() + Dice::Get()->Throw(),
      Dice::Get()->Throw(),
      Item::luck_potion
    );

    const Game game1(seed,character1);

    Dice::Get()->SetSeed(seed);

    Character character2(
      Dice::Get()->Throw(),
      Dice::Get()->Throw() + Dice::Get()->Throw(),
      Dice::Get()->Throw(),
      Item::luck_potion
    );

    const Game game2(seed,character2);
    assert(character1.GetChapters() == character2.GetChapters());
  }
  if (verbose) { std::clog << "Can the game be won?" << std::endl; }
  {
    const int seed{0};
    //Use a maxed-out character
    const Character character(6,12,12,Item::luck_potion);
    Walkthrough walkthrough(seed,character);
    walkthrough.Start();
  }
}
#endif
