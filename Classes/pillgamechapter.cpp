#include "pillgamechapter.h"

#include "chapter.h"
#include "character.h"
#include "dice.h"
#include "helper.h"

PillGameChapter::PillGameChapter(Chapter& chapter)
  : m_chapter{chapter}
{

}

void PillGameChapter::Do(Character& character) const
{
  const int dice{Dice::Get()->Throw()};
  if (dice == 1)
  {
    m_chapter.ShowText(
      "You die quickly from the poisoned pill and your adventure ends here.\n"
    );
    character.SetIsDead();
  }
}
