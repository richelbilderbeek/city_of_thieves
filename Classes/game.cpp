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
  Dice::Get()->SetSeed(rng_seed);
}

void Game::DoChapter()
{
  if (m_has_lost || m_has_won) return;
  assert(!IsDead(m_character));

  const int chapter_number{GetCurrentChapterNumber()};

  const Chapter chapter(chapter_number);
  chapter.SetObserver(m_observer);

  chapter.Do(m_character);

  if (IsDead(m_character)) { m_has_lost = true; }
  if (chapter_number == 400)
  {
    assert(!IsDead(m_character));
    m_has_won = true;
  }
}

int Game::GetCurrentChapterNumber() const noexcept
{
  return GetCurrentChapter(m_character);
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
