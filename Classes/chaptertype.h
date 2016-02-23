#ifndef CHAPTERTYPE_H
#define CHAPTERTYPE_H

#include <string>

enum class ChapterType
{
  fight,
  game_lost,
  game_won,
  normal,
  pawn_shop, //Chapter 354
  play_ball, //Chapter 378
  play_dice, //Chapter 206
  play_pill, //Chapter 223
  shop,
  test_your_luck,
  test_your_skill
};

std::string ToPrettyStr(const ChapterType item);
std::string ToStr(const ChapterType item);

ChapterType ToChapterType(const std::string& item_name);
bool IsChapterType(const std::string& item_name);
std::ostream& operator<<(std::ostream& os, const ChapterType item);

ChapterType ReadChapterType(std::stringstream& s);


#endif // CHAPTERTYPE_H
