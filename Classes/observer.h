#ifndef OBSERVER_H
#define OBSERVER_H

#include <vector>
#include "option.h"

struct Character;

struct Observer
{
  virtual ~Observer() {}
  virtual void CharacterChanged(const Character& character) = 0;
  virtual int GetNumberOfCharsPerLine() const noexcept = 0;
  virtual void ShowText(const std::string& text) = 0;
  virtual void Wait() = 0;
  virtual Option RequestOption(const std::vector<Option>& options) = 0;
};

/// Get the default number of characters per line,
/// which is 80 on a terminal and 32 on an NDS
int GetDefaultNumberOfCharsPerLine() noexcept;

#endif // OBSERVER_H
