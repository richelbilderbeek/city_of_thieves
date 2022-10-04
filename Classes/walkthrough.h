#ifndef WALKTHROUGH_H
#define WALKTHROUGH_H

#include <string>
#include <vector>

#include "option.h"
#include "game.h"
#include "observer.h"
#include "route.h"

struct Walkthrough final : public Observer
{
  Walkthrough(
    const int seed,
    const Character& character,
    const bool silent = false,
    const std::vector<int>& route = GetWinningRoute()
  );

  int GetNumberOfCharsPerLine() const noexcept override;
  void Start();

  private:

  Game m_game;
  std::vector<int> m_route;
  bool m_silent;

  void CharacterChanged(const Character&) override {} //Ignore
  Option RequestOption(const std::vector<Option>& options) override;
  void ShowText(const std::string& text) override;
  void Wait() override;
};

#endif // WALKTHROUGH_H
