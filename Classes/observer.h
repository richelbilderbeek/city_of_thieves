#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "option.h"

struct Character;

struct Observer
{
  virtual ~Observer() {}

  /// Slot that is called when a character is changed
  virtual void CharacterChanged(const Character& character) = 0;

  /// Get the number of character for the terminal/NDS
  virtual int GetNumberOfCharsPerLine() const noexcept = 0;

  /// Show text in the way of a terminal/NDS
  virtual void ShowText(const std::string& text) = 0;

  /// Wait in the way of a terminal/NDS
  virtual void Wait() = 0;

  /// Wait in the way of a terminal/NDS
  virtual Option RequestOption(const std::vector<Option>& options) = 0;
};

/// Get the default number of characters per line,
/// which is 80 on a terminal and 32 on an NDS
int GetDefaultNumberOfCharsPerLine() noexcept;

#endif // OBSERVER_H
