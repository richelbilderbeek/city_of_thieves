#include "gamewonchapter.h"

#include "gamelostchapter.h"

#include "character.h"
#include "chapter.h"

GameWonChapter::GameWonChapter(Chapter * const chapter)
  : m_chapter{chapter}
{
}

void GameWonChapter::Do(Character& character) const
{
  character.SetIsDead();
  m_chapter->ShowText(
    "GAME WON! CONGRATULATIONS!\n"
  );
}
