#include "skillchapter.h"

#include <sstream>

#include "chapter.h"
#include "character.h"
#include "helper.h"

SkillChapter::SkillChapter(Chapter& chapter)
  :
    m_chapter{chapter},
    m_skill_consequence{},
    m_skill_text{},
    m_no_skill_consequence{},
    m_no_skill_text{}
{

}

void SkillChapter::Do(Character& character) const
{
  m_chapter.ShowText("You test your skill...\n");
  m_chapter.Wait();

  if (character.TestSkill())
  {
    m_chapter.ShowText("Skill!\n" + GetSkillText() + "\n");
    GetSkillConsequence().Apply(character);
  }
  else
  {
    m_chapter.ShowText("No skill!\n" + GetNoSkillText() + "\n");
    GetNoSkillConsequence().Apply(character);
  }
}
