#ifndef DICEGAMECHAPTER_H
#define DICEGAMECHAPTER_H

struct Chapter;
struct Character;

struct DiceGameChapter
{
  DiceGameChapter(Chapter& chapter);

  ///Let the character undergo this chapter
  void Do(Character& character) const;

  private:
  Chapter& m_chapter;
};

#endif // DICEGAMECHAPTER_H
