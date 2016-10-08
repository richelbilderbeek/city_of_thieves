#include "terminal.h"

#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "chapter.h"
#include "game.h"
#include "getfile.h"
#include "helper.h"

Terminal::Terminal()
  :
    m_auto_play{false},
    m_silent{false},
#ifndef NDEBUG
    m_wait_character_msec{0.0},
    m_wait_suspense{0.0}
#else
    m_wait_character_msec{0.01},
    m_wait_suspense{0.5}
#endif
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
}

void Terminal::ConnectTo(const Chapter& chapter)
{
  chapter.SetObserver(this);
}

void Terminal::ConnectTo(const Game& game)
{
  game.SetObserver(this);
}

void Terminal::CharacterChanged(const Character& /* character */)
{
  #ifndef NDEBUG
  ShowText("Character has changed\n");
  #endif
}

int Terminal::GetNumberOfCharsPerLine() const noexcept
{
#ifndef ARM9
  return 80;
#else
  return 32;
#endif
}

Option Terminal::RequestOption(const std::vector<Option>& options)
{
  assert(!options.empty());
  const int n_options{static_cast<int>(options.size())};

  while (1)
  {
    std::vector<int> valid_indices;
    for (int i=0; i!=n_options; ++i)
    {
      valid_indices.push_back(i);
      assert(options[i].GetText().back() != '\n');
      std::stringstream text;
      text << "[" << i << "] " << options[i].GetText() << '\n';
      ShowText(text.str());
    }
    const int chosen_index{SlotRequestInput(valid_indices)};
    assert(chosen_index >= 0);
    assert(chosen_index < n_options);
    return options[chosen_index];
  }
}

int Terminal::SlotRequestInput(const std::vector<int>& valid_inputs)
{
  assert(!valid_inputs.empty());
  if (valid_inputs.size() == 1) { return valid_inputs[0]; }
  if (m_auto_play)
  {
    return valid_inputs[0] == 0 ? valid_inputs[1] : valid_inputs[0];
  }
  else
  {
    while (1)
    {
      std::string s;
      std::getline(std::cin,s);
      if (!Helper().IsInt(s))
      {
        ShowText("Please enter an integer\n");
        continue;
      }
      const int i{Helper().ToInt(s)};
      const auto iter = std::find(std::begin(valid_inputs),std::end(valid_inputs),i);
      if (iter == std::end(valid_inputs))
      {
        std::stringstream t;
        std::copy(std::begin(valid_inputs),std::end(valid_inputs),std::ostream_iterator<int>(t,", "));
        std::string u{t.str()};
        u.pop_back(); u.pop_back(); //Pop the tailing comma and space
        ShowText("Please enter a valid input: " + u + "\n");
        continue;
      }
      return *iter;
    }
  }
}

void Terminal::ShowText(const std::string& text)
{
  if (m_verbose) { std::clog << "Terminal::ShowText: showing " << text << std::endl; }
  if (m_silent) return;

  const std::string lines = Helper().StrToLines(text,GetNumberOfCharsPerLine());
  for (const char c: lines)
  {
    Helper().Cout(c);
    #ifndef ARM9
    std::cout.flush();
    #endif
    Helper().Wait(m_wait_character_msec);
  }
}

void Terminal::SpeakText(const std::string& text)
{
  std::ofstream f("espeak.txt");
  f << text;
  f.close();
  const int error{std::system("espeak -f espeak.txt")};
  assert(!error);
  if (error) {;}
}

void Terminal::Wait()
{
  Helper().Wait(m_wait_suspense);
}

