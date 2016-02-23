#ifndef GAME_H
#define GAME_H



#include "character.h"
#include "option.h"

struct Observer;

struct Game
{
  Game(
    const int rng_seed,
    const Character& character
  );
  Game(const Game& game) = delete;
  Game& operator=(const Game& game) = delete;

  void DoChapter();
  const Character& GetCharacter() const noexcept { return m_character; }
  bool HasLost() const noexcept { return m_has_lost; }
  bool HasWon() const noexcept { return m_has_won; }
  int GetCurrentChapterNumber() const noexcept;

  #ifndef NDEBUG
  void SetChapter(const int chapter);
  #endif

  void SetObserver(Observer * const observer) const { m_observer = observer; }

  private:
  Character m_character;
  bool m_has_lost;
  bool m_has_won;

  mutable Observer * m_observer;

  static const bool m_verbose{false};

  void SlotCharacterChanged(const Character& character);
  Option SlotRequestOption(const std::vector<Option>& valid_inputs);
  void SlotShowText(const std::string& text);
  void SlotWait();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // GAME_H
