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

  /// Get the summed consequence of this route
  const Consequence& GetConsequence() noexcept { return m_consequence; }

  int GetNumberOfCharsPerLine() const noexcept override;

  /// Run the route, get the change in character
  Character Run();

  private:

  Game m_game;
  std::vector<int> m_route;
  bool m_silent;

  /// The summed consequence of this route till now
  Consequence m_consequence;

  void CharacterChanged(const Character&) override {} //Ignore
  Option RequestOption(const std::vector<Option>& options) override;
  void ShowText(const std::string& text) override;
  void Wait() override;
};

#endif // WALKTHROUGH_H
