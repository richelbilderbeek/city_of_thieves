#ifndef GAMELOSTCHAPTER_H
#define GAMELOSTCHAPTER_H

struct Chapter;
struct Character;

struct GameLostChapter
{
  GameLostChapter(Chapter * const chapter);
  GameLostChapter(const GameLostChapter&) = default;
  GameLostChapter& operator=(const GameLostChapter&) = default;

  void Do(Character& character) const;

  private:
  Chapter * m_chapter; //Will always point to its Chapter
};

#endif // GAMELOSTCHAPTER_H
