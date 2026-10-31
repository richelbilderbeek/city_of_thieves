#ifndef OPTIONSCHAPTER_H
#define OPTIONSCHAPTER_H

#include <random>
#include <vector>
#include "option.h"

///Chapter in which the player has to choose an option
///
/// Note: I worry that using a fresh RNG generator
/// per chapter results in a predictable randomness
struct OptionsChapter
{
  using Options = std::vector<Option>;

  OptionsChapter();

  void AddOption(const Option& option);


  const Options& GetOptions() const noexcept { return m_options; }

  Options GetValidOptions(const Character& character) const noexcept;

  private:

  Options m_options;
  std::mt19937 m_rng_generator;
};

#endif // OPTIONSCHAPTER_H
