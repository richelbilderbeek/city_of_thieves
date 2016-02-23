#ifndef FIGHTINGCHAPTER_H
#define FIGHTINGCHAPTER_H

#include <vector>

#include "monster.h"

struct Chapter;
struct Character;

///A chapter in which a fight takes place
///FightingChapter is a State of Chapter
struct FightingChapter
{
  FightingChapter(Chapter& chapter);

  void AddMonster(const Monster& monster);

  void Do(Character& character) const;

  ///Battle the monsters one by one
  bool DoFightSequentially() const noexcept { return m_fight_sequentially; }

  const std::vector<Monster>& GetMonsters() const noexcept { return m_monsters; }

  ///At which round can the player escape? 1000 if player cannot
  int GetRoundsToEscape() const noexcept { return m_rounds_to_escape; }

  ///If the player escapes, which chapter will he/she go to? -1 if player cannot escape
  int GetEscapeToChapter() const noexcept { return m_escape_chapter; }

  void SetEscapeToChapter(const int escape_to_chapter);

  void SetFightSequentially(const bool fight_sequentially) { m_fight_sequentially = fight_sequentially; }

  void SetRoundsToEscape(const int rounds_to_escape);

  void SetVerbose(const bool verbose) const noexcept;

  private:

  Chapter& m_chapter;

  ///If the player escapes a monster fight, to which chapter?
  int m_escape_chapter;

  ///Is the fight sequentially (one after one) or are the monster fought both at the same time?
  bool m_fight_sequentially;

  std::vector<Monster> m_monsters;

  int m_rounds_to_escape;

  mutable bool m_verbose;

  void DoFight(std::vector<Monster> monsters,Character& character) const;
  void DoFight(Monster monster,Character& character) const;
  void DoFightTwoMonsters(std::vector<Monster> monsters,Character& character) const;
};


#endif // FIGHTINGCHAPTER_H
