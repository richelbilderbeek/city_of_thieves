#ifndef OPTIONSCHAPTER_H
#define OPTIONSCHAPTER_H

#include <vector>
#include "option.h"

///Chapter in which the player has to choose an option
struct OptionsChapter
{
  using Options = std::vector<Option>;

  OptionsChapter();

  void AddOption(const Option& option);


  const Options& GetOptions() const noexcept { return m_options; }

  Options GetValidOptions(const Character& character) const noexcept;

  private:

  Options m_options;
};

#endif // OPTIONSCHAPTER_H
