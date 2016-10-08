#ifndef HELPER_H
#define HELPER_H

#include <iosfwd>
#include <string>
#include <vector>

struct Helper
{
  Helper();

  void Cout(const char c) const;
  void Cout(const std::string& s) const;
  void CoutNl(const std::string& s) const;

  void CreateGraph() const;

  ///Is x between a and b?
  bool IsBetween(const double x, const double a, const double b) const;

  bool IsInt(const std::string& s) const noexcept;

  ///Determines if a filename is a regular file
  ///From http://www.richelbilderbeek.nl/CppIsRegularFile.htm
  bool IsRegularFile(const std::string& filename) const;

  void Parse(std::stringstream& s, const char expected_char) const;

  char ReadChar(std::stringstream& s) const;
  int ReadInt(std::stringstream& s) const;
  std::string ReadString(std::stringstream& s) const;

  ///Read text until @
  std::string ReadText(std::stringstream& s) const;

  ///Strip only the first character of the first line
  std::vector<std::string> StripFirstChar(std::vector<std::string> v) const;

  ///From http//www.richelbilderbeek.nl/CppStrToLines.htm
  ///Add newlines to a std::string so that
  ///each line has length characters at most
  std::string StrToLines(std::string s, const int length) const;

  int ToInt(const std::string& s) const;

  ///Replace 'two_words' by 'two words'
  std::string ToPretty(std::string s) const;


  std::string ToStr(const int i) const;

  ///Trim leading and trailing whitespace
  //From http://www.richelbilderbeek.nl/CppTrim.htm
  std::string Trim(const std::string& s) const;

  void Wait(const double n_secs) const noexcept;
};

#endif // HELPER_H
