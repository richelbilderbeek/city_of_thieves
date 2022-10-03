#include "helper.h"

#include <algorithm>
#include <cassert>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>

#include "ai.h"
#include "chapter.h"
#include "chaptertype.h"
#include "fightingchapter.h"
#include "monster.h"

#ifdef ARM9
#include <nds.h>
#include <stdio.h>
#endif

Helper::Helper()
{

}

void Helper::Cout(const char c) const
{

  #ifdef ARM9
  char buffer[2];
  buffer[0] = c;
  buffer[1] = '\0';
  printf(buffer);
  #else
  std::cout << c;
  #endif
}

void Helper::Cout(const std::string& s) const
{
  #ifdef ARM9
  printf(s.c_str());
  fflush(stdout);
  #else
  std::cout << s;
  #endif
}

void Helper::CoutNl(const std::string& s) const
{
  Cout(s + "\n");
}

void Helper::CreateGraph() const
{
  const std::string filename_base{"Graph"};
  const std::string dot_filename{filename_base + ".dot"};
  const std::string png_filename{filename_base + ".png"};
  std::ofstream f(dot_filename);

  f << "digraph CityOfThieves {\n";
  for (int i=1; i!=450; ++i)
  {
    try
    {
      const Chapter chapter(i);
      //Label node according to chapter type
      std::string node_color = "black";
      std::string labeltext{Helper().ToStr(chapter.GetChapterNumber())};
      switch (chapter.GetType())
      {
        case ChapterType::fight:
          node_color = "red";
          labeltext += std::string(" ")
            + MonstersToStr(chapter.GetFighting().GetMonsters());
          break;
        case ChapterType::test_your_luck: node_color = "blue"; break;
        case ChapterType::test_your_skill: node_color = "green"; break;
        case ChapterType::normal:
          labeltext += std::string(" ")
            + SummarizeChapter(chapter.GetChapterNumber());
        default: break; //OK
      }
      //Shape for special chapter
      std::string shape{"ellipse"};
      switch (i)
      {
        case 7: case 111: //Black pearls
        case 191: case 237: //Lotus flower
        case 82: case 303: //Hag's hair
        case 42: case 85: //Silver arrow
        case 279: //Tattoo
        case 163: //Ring of the golden eye
          shape = "doublecircle";
        default: break;
      }
      f << i
        << "["
        << "label=\""
        << labeltext
        << "\" shape=" << shape
        << " color=" << node_color
        << "];\n"
      ;
      if (chapter.GetNextChapter() != -1)
      {
        f << i << "->" << chapter.GetNextChapter() << ";\n";
      }
      else if (!chapter.GetFighting().GetMonsters().empty())
      {
        if (chapter.GetFighting().GetEscapeToChapter() != -1)
        {
          f << i << "->" << chapter.GetFighting().GetEscapeToChapter() << " [ label=\"Escape\"];\n";
        }
      }
      else if (!chapter.GetLuck().GetLuckText().empty())
      {
        f << i << "->" << chapter.GetLuck().GetLuckChapter() << " [ label=\"Luck\"];\n";
        f << i << "->" << chapter.GetLuck().GetNoLuckChapter() << " [ label=\"No luck\"];\n";
      }
      else if (!chapter.GetOptions().GetOptions().empty())
      {
        for (const auto& option: chapter.GetOptions().GetOptions())
        {
          //f << i << "->" << option.GetNextChapter() << " [ label=\"Choice\"];\n";
          f << i << "->" << option.GetNextChapter() << " [ label=\""<< option.GetText() <<  "\"];\n";
        }
      }
      else if (!chapter.GetSkill().GetSkillText().empty())
      {
        f << i << "->" << chapter.GetSkill().GetSkillConsequence().GetNextChapter() << " [ label=\"Skill\"];\n";
        f << i << "->" << chapter.GetSkill().GetNoSkillConsequence().GetNextChapter() << " [ label=\"No skill\"];\n";
      }
      else if (chapter.GetType() == ChapterType::game_lost)
      {
        f << i << "-> GameOver;\n";
      }
      else if (chapter.GetType() == ChapterType::game_won)
      {
        f << i << "-> GameWon;\n";
      }
    }
    catch (const std::logic_error& )
    {
      //f << i << ": FAIL" << std::endl;
    }
    catch (const std::runtime_error&)
    {
      //f << i << ": not present" << std::endl;
    }
  }
  f << "}\n";
  f.close();
  {
    std::stringstream cmd;
    cmd << "dot -Tpng " << dot_filename << " > " << png_filename;
    const int error{std::system(cmd.str().c_str())};
    assert(!error);
    if (error) {;}
  }
}

bool Helper::IsBetween(const double x, const double a, const double b) const
{
  // a < x < b
  if (a <= x && x <= b) return true;
  if (b <= x && x <= a) return true;
  return false;
}

///IsInt determines if std::string can be converted to integer.
///From http://www.richelbilderbeek.nl/CppIsInt.htm
bool Helper::IsInt(const std::string& s) const noexcept
{
  std::istringstream i(s);
  int temp{0};
  i >> temp;
  if (!i) return false;
  char c{'\0'}; //Should be at end, if not, the string contained more than just a number
  i >> c;
  if (i) return false;
  return true;
}


bool Helper::IsRegularFile(const std::string& filename) const
{
  std::fstream f;
  f.open(filename.c_str(),std::ios::in);
  return f.is_open();
}

void Helper::Parse(std::stringstream& s, const char expected_char) const
{
  const char c = ReadChar(s);
  if (c != expected_char) { std::cerr << "WARNING: expected character" << std::endl; }
  assert(c == expected_char);
}

char Helper::ReadChar(std::stringstream& s) const
{
  char c = '\0';
  assert(!s.eof());
  s >> c;
  assert(!s.eof());
  while (!s.eof() && (c == '\n' || c == ' ' || c == '\0')) { s >> c; }
  assert(!s.eof());
  return c;
}


int Helper::ReadInt(std::stringstream& s) const
{
  int number = -9999;
  s >> number;
  assert(number > -9999);
  return number;
}

std::string Helper::ReadString(std::stringstream& s) const
{
  std::string str = "";
  s >> str;
  return str;
}

std::string Helper::ReadText(std::stringstream& s) const
{
  s << std::noskipws; //Obligatory
  //Show text until @
  std::string text;
  //int pos = 0;
  char prev_c = ' ';
  while (1)
  {
    char c;
    s >> c;
    if (c == '@')
    {
      break;
    }
    if (c == '\n') c = ' '; //Convert a newline to space, so input files do not require a space after every line
    if (c == ' ' && prev_c == ' ') continue; //Tweede spatie overslaan
    text += c;
    prev_c = c;
  }
  s << std::skipws; //Obligatory

  text = Trim(text); //Remove the space between text and @
  return text;
}


std::vector<std::string> Helper::StripFirstChar(std::vector<std::string> v) const
{
  assert(!v.empty());
  assert(!v[0].empty());
  v[0] = v[0].substr(1,v[0].size() - 1);
  return v;
}

int Helper::ToInt(const std::string& s) const
{
  #ifndef ARM9
  return std::stoi(s);
  #else
  return std::atoi(s.c_str());
  #endif
}

std::string Helper::StrToLines(std::string s, const int length) const
{
  assert(length > 0);
  const int sz{static_cast<int>(s.size())};
  int this_line_start = 0;
  while (1)
  {
    //Is there still work to do
    if (this_line_start + length >= sz) { return s; }

    bool done = false;

    //Do a forward scan for a newline
    for (int pos = this_line_start; pos != this_line_start + length; ++pos)
    {
      assert(pos < this_line_start + length);
      if (s[pos] == '\n')
      {
        this_line_start = pos + 1;
        done = true;
        break;
      }
    }
    if (done) continue;

    //Do a backward scan for a space
    for (int pos = this_line_start + length; pos != this_line_start; --pos)
    {
      assert(pos > this_line_start);
      if (s[pos] == ' ')
      {
        s[pos] = '\n';
        this_line_start = pos + 1;
        done = true;
        break;
      }
    }
    if (done) continue;

    //There is no space to be found, inserting it
    s = s.substr(0,this_line_start+length)
      + "\n"
      + s.substr(this_line_start+length,sz-this_line_start-length)
    ;
    this_line_start = this_line_start + length + 1;
  }
  /*

  while (1)
  {
    if (pos >= sz) break;
    assert(pos >= 0 && pos < sz);
    if (s[pos] == '\n')
    {
      if (verbose) { std::clog << "Found newline at pos " << pos << std::endl; }
      this_line_start = pos + 1;
      pos = this_line_start + length;

      if (verbose) { std::clog << "New pos: " << pos << std::endl; }
      if (verbose) { std::clog << "New this_line_start: " << this_line_start << std::endl; }
      continue;
    }
    if (s[pos] == ' ')
    {
      if (verbose) { std::clog << "Found space at pos " << pos << " which is replaced by a newline" << std::endl; }

      s[pos] = '\n';
      this_line_start = pos + 1;
      pos = this_line_start + length;

      if (verbose) { std::clog << "New pos: " << pos << std::endl; }
      if (verbose) { std::clog << "New this_line_start: " << this_line_start << std::endl; }
    }
    if (pos >= sz) break;
    --pos;
    assert(pos >= this_line_start);
    if (pos == this_line_start)
    {
      if (verbose) { std::clog << "Word is longer than length, insert a newline in the word" << std::endl; }
      s = s.substr(0,this_line_start+length)
        + "\n"
        + s.substr(this_line_start+length,sz-this_line_start-length)
      ;

      if (verbose) { std::clog << "New string: " << s << std::endl; }

      this_line_start = this_line_start + length + 1;
      pos = this_line_start + length;

      if (verbose) { std::clog << "New pos: " << pos << std::endl; }
      if (verbose) { std::clog << "New this_line_start: " << this_line_start << std::endl; }

      assert(pos >= this_line_start);
    }
  }
  return s;
  */
}

std::string Helper::ToPretty(std::string s) const
{
  assert(!s.empty());
  if (s == "carralifs_sword") { return "Carralif's sword"; }
  if (s == "fatnose") { return "troll named Fatnose"; }
  if (s == "sourbelly") { return "troll named Sourbelly"; }
  std::replace(
    std::begin(s),
    std::end(s),
    '_',' '
  );
  s[0] = std::tolower(s[0]);
  return s;
}

std::string Helper::ToStr(const int i) const
{
  #ifndef ARM9
  return std::to_string(i);
  #else
  std::ostringstream s;
  if (!(s << i)) throw std::logic_error("IntToStr failed");
  return s.str();
  #endif
}

std::string Helper::Trim(const std::string& s) const
{
  const int size{static_cast<int>(s.size())};
  int pos_begin = -1;
  int pos_end = size-1;
  for (int i=0; i!=size; ++i)
  {
    if (s[i]!=' ' && s[i]!='\n' && s[i]!='\t')
    {
      pos_begin = i; break;
    }
  }
  if (pos_begin == -1) return "";
  for (int i=size-1; i!=-1; --i)
  {
    if (s[i]!=' ' && s[i]!='\n' && s[i]!='\t')
    {
      pos_end = i; break;
    }
  }
  return s.substr(pos_begin,pos_end-pos_begin+1);
}

void Helper::Wait(const double n_secs, const bool verbose) const noexcept
{
  if (verbose) { std::clog << __func__ << std::endl; }
  #ifndef ARM9
  const auto t = std::chrono::high_resolution_clock::now();

  while (1)
  {
    const auto d = std::chrono::high_resolution_clock::now() - t;
    const long long int n_msecs_passed{std::chrono::duration_cast<std::chrono::milliseconds>(d).count()};
    const double secs_passed{static_cast<double>(n_msecs_passed) / 1000.0};
    if (secs_passed > n_secs) return;
  }
  #else
  //std::chrono::high_resolution_clock does not work on NDS
  const int n{static_cast<int>(n_secs * 200.0)};
  if (verbose) { std::clog << "n: " << n << std::endl; }
  for (int i=0; i!=n; ++i)
  {
    //swiWaitForVBlank();
    if (verbose) std::cout << i << ' ';
  }
  #endif
  if (verbose) { std::clog << "End of " << __func__ << std::endl; }
}
