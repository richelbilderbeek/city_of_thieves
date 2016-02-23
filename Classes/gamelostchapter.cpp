#include "gamelostchapter.h"

#include "character.h"
#include "chapter.h"

GameLostChapter::GameLostChapter(Chapter * const chapter)
  : m_chapter{chapter}
{
}

void GameLostChapter::Do(Character& character) const
{
  character.SetIsDead();
  m_chapter->ShowText(
    "GAME OVER\n"
  );
}
