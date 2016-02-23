#ifndef SKILLCHAPTER_H
#define SKILLCHAPTER_H

#include <string>

#include "consequence.h"

struct Chapter;
struct Character;

///Chapter in which you have to test your skill
struct SkillChapter
{
  SkillChapter(Chapter& chapter);

  ///Let the character undergo this chapter
  void Do(Character& character) const;

  const std::string& GetSkillText() const noexcept { return m_skill_text; }
  const std::string& GetNoSkillText() const noexcept { return m_no_skill_text; }
  const Consequence& GetSkillConsequence() const noexcept { return m_skill_consequence; }
  const Consequence& GetNoSkillConsequence() const noexcept { return m_no_skill_consequence; }

  void SetSkillText(const std::string& skill_text) noexcept { m_skill_text = skill_text; }
  void SetNoSkillText(const std::string& no_skill_text) noexcept { m_no_skill_text = no_skill_text; }
  void SetSkillConsequence(const Consequence& consequence) noexcept { m_skill_consequence = consequence; }
  void SetNoSkillConsequence(const Consequence& consequence) noexcept { m_no_skill_consequence = consequence; }

  private:

  Chapter& m_chapter;

  Consequence m_skill_consequence;
  std::string m_skill_text;
  Consequence m_no_skill_consequence;
  std::string m_no_skill_text;

};

#endif // SKILLCHAPTER_H
