#ifndef MENUDIALOG_H
#define MENUDIALOG_H

#include "option.h"

struct Observer;

struct MenuDialog
{
  MenuDialog();

  void Execute();

  void SetObserver(Observer * const observer) { m_observer = observer; }

  private:

  Observer * m_observer;

  static const bool m_verbose{false};

  Character CreateCharacter() const noexcept;

  std::string GetAboutText() const noexcept { return "About"; }
  std::string GetCreateGraphText() const noexcept { return "Create graph"; }
  std::string GetHintsText() const noexcept { return "Hints"; }
  std::string GetIntroductionText() const noexcept { return "Introduction"; }
  std::string GetManualText() const noexcept { return "Manual"; }
  std::vector<Option> GetMenuOptions() const noexcept;
  std::string GetQuitText() const noexcept { return "Quit"; }
  std::string GetSolveGameText() const noexcept { return "Solve game"; }
  std::string GetStartGameText() const noexcept { return "Start game"; }
  std::string GetTeaserText() const noexcept { return "Teaser"; }

  void ShowAbout();
  void ShowIntroduction();
  void ShowManual();
  void ShowTeaser();
  void ShowHints();

  void CharacterChanged(const Character& character) const;
  Option RequestOption(const std::vector<Option>& valid_inputs) const;
  void ShowText(const std::string& text) const;
  void Wait() const;

  void StartGame();

  #ifndef NDEBUG
  static void Test() noexcept;
  #endif
};

#endif // MENUDIALOG_H
