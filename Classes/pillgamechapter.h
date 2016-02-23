#ifndef PILLGAMECHAPTER_H
#define PILLGAMECHAPTER_H

struct Chapter;
struct Character;

struct PillGameChapter
{
  PillGameChapter(Chapter& chapter);

  ///Let the character undergo this chapter
  void Do(Character& character) const;

  private:
  Chapter& m_chapter;
};

#endif // PILLGAMECHAPTER_H
