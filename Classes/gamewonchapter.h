#ifndef GAMEWONCHAPTER_H
#define GAMEWONCHAPTER_H

struct Chapter;
struct Character;

struct GameWonChapter
{
  GameWonChapter(Chapter * const chapter);
  GameWonChapter(const GameWonChapter&) = default;
  GameWonChapter& operator=(const GameWonChapter&) = default;

  void Do(Character& character) const;

  private:
  Chapter * m_chapter; //Will always point to its Chapter
};

#endif // GAMEWONCHAPTER_H
