#ifndef BALLGAMECHAPTER_H
#define BALLGAMECHAPTER_H

struct Chapter;
struct Character;

struct BallGameChapter
{
  BallGameChapter(Chapter& chapter);

  ///Let the character undergo this chapter
  void Do(Character& character) const;

  private:
  Chapter& m_chapter;
};

#endif // BALLGAMECHAPTER_H
