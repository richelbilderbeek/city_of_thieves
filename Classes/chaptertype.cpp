#include "chaptertype.h"

#include <algorithm>
#include <cassert>
#include <sstream>
#include <stdexcept>

#include "helper.h"

std::vector<std::pair<ChapterType,std::string>> CreateChapterTypeBimap()
{
  using Pair = std::pair<ChapterType,std::string>;
  static std::vector<Pair> m;
  {
    static bool is_done{false};
    if (is_done) return m;
    is_done = true;
  }
  m.push_back(Pair(ChapterType::fight,"fight"));
  m.push_back(Pair(ChapterType::game_lost,"game_lost"));
  m.push_back(Pair(ChapterType::game_won,"game_won"));
  m.push_back(Pair(ChapterType::normal,"normal"));
  m.push_back(Pair(ChapterType::pawn_shop,"pawn_shop"));
  m.push_back(Pair(ChapterType::play_ball,"play_ball"));
  m.push_back(Pair(ChapterType::play_dice,"play_dice"));
  m.push_back(Pair(ChapterType::play_pill,"play_pill"));
  m.push_back(Pair(ChapterType::shop,"shop"));
  m.push_back(Pair(ChapterType::test_your_luck,"test_your_luck"));
  m.push_back(Pair(ChapterType::test_your_skill,"test_your_skill"));
  return m;
}

bool IsChapterType(const std::string& item_name)
{
  using Pair = std::pair<ChapterType,std::string>;
  const auto m = CreateChapterTypeBimap();
  return std::find_if(
    std::begin(m),
    std::end(m),
    [item_name](const Pair& p) { return p.second == item_name; }
  ) != std::end(m);
}

ChapterType ReadChapterType(std::stringstream& s)
{
  const std::string t{Helper().ReadString(s)};
  if (!IsChapterType(t))
  {
    std::stringstream error;
    error << "Cannot read chapter type '" << t << "'";
    throw std::runtime_error(error.str());
  }
  return ToChapterType(t);
}

ChapterType ToChapterType(const std::string& item_name)
{
  assert(IsChapterType(item_name));
  using Pair = std::pair<ChapterType,std::string>;
  const auto m = CreateChapterTypeBimap();
  return std::find_if(
    std::begin(m),
    std::end(m),
    [item_name](const Pair& p) { return p.second == item_name; }
  )->first;
}

std::string ToPrettyStr(const ChapterType item)
{
  return Helper().ToPretty(ToStr(item));
}

std::string ToStr(const ChapterType item)
{
  using Pair = std::pair<ChapterType,std::string>;
  const auto m = CreateChapterTypeBimap();
  const auto iter = std::find_if(
    std::begin(m),
    std::end(m),
    [item](const Pair& p) { return p.first == item; }
  );
  assert(iter != std::end(m));
  return iter->second;
}

std::ostream& operator<<(std::ostream& os, const ChapterType item)
{
  os << ToStr(item);
  return os;
}
