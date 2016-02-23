#include "optionschapter.h"

#include <algorithm>

#include "character.h"

OptionsChapter::OptionsChapter()
  : m_options{}
{

}

void OptionsChapter::AddOption(const Option& option)
{
  m_options.push_back(option);
  std::random_shuffle(std::begin(m_options),std::end(m_options));
}

std::vector<Option> OptionsChapter::GetValidOptions(const Character& character) const noexcept
{
  std::vector<Option> valid_options;
  std::copy_if(
    std::begin(m_options),
    std::end(m_options),
    std::back_inserter(valid_options),
    [&character](const Option& option)
    {
      return option.CanChoose(character);
    }
  );
  return valid_options;
}
