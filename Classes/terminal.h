#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>

#include "option.h"
#include "observer.h"
struct Chapter;
struct Game;

///Shows the Game
struct Terminal final : public Observer
{
  Terminal();

  void ConnectTo(const Chapter& chapter);
  void ConnectTo(const Game& chapter);

  int GetNumberOfCharsPerLine() const noexcept override;

  void SetAutoPlay(const bool auto_play) { m_auto_play = auto_play; }
  void SetSilent(const bool silent) { m_silent = silent; }

  //void SetNumberOfCharsPerLine(const int n_chars) { m_n_chars = n_chars; }

  void SpeakText(const std::string& text);


  void CharacterChanged(const Character& character) override;
  int SlotRequestInput(const std::vector<int>& valid_inputs);
  Option RequestOption(const std::vector<Option>& valid_inputs) override;
  void ShowText(const std::string& text) override;
  void Wait() override;

  private:

  bool m_auto_play;

  bool m_silent;

  static const bool m_verbose{false};

  ///Waiting time between characters in millisecs
  double m_wait_character_msec;

  ///Waiting time to increase the suspense
  double m_wait_suspense;
};

#endif // TERMINAL_H
