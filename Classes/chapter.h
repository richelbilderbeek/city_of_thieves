#ifndef CHAPTER_H
#define CHAPTER_H

#include <string>
#include <vector>



#include "chaptertype.h"
#include "character.h"
#include "fightingchapter.h"
#include "luckchapter.h"
#include "optionschapter.h"
#include "pawnshopchapter.h"
#include "shopchapter.h"
#include "skillchapter.h"
#include "gamelostchapter.h"
#include "gamewonchapter.h"
#include "consequence.h"
#include "ballgamechapter.h"
#include "dicegamechapter.h"
#include "pillgamechapter.h"

struct Observer;

struct Chapter
{
  Chapter(const int chapter_number);
  Chapter(const Chapter&) = delete;
  Chapter& operator=(const Chapter&) = delete;

  ///Let the player do this chapter
  void Do(Character& character) const;

  ///The text displayed at the end of the chapter
  const std::string& GetByeText() const noexcept { return m_bye_text; }

  int GetChapterNumber() const noexcept { return m_chapter_number; }

  const Consequence& GetConsequence() const noexcept { return m_consequence; }

  const FightingChapter& GetFighting() const noexcept { return m_fighting_chapter; }
  FightingChapter& GetFighting() noexcept { return m_fighting_chapter; }

  const LuckChapter& GetLuck() const noexcept { return m_luck_chapter; }
  LuckChapter& GetLuck() noexcept { return m_luck_chapter; }

  int GetNextChapter() const noexcept { return m_consequence.GetNextChapter(); }

  Observer * GetObserver() const noexcept { return m_observer; }

  const OptionsChapter& GetOptions() const noexcept { return m_options_chapter; }
  OptionsChapter& GetOptions() noexcept { return m_options_chapter; }

  const PawnShopChapter& GetPawnShop() const noexcept { return m_pawn_shop_chapter; }
  PawnShopChapter& GetPawnShop() noexcept { return m_pawn_shop_chapter; }

  const ShopChapter& GetShop() const noexcept { return m_shop_chapter; }
  ShopChapter& GetShop() noexcept { return m_shop_chapter; }

  const SkillChapter& GetSkill() const noexcept { return m_skill_chapter; }
  SkillChapter& GetSkill() noexcept { return m_skill_chapter; }

  std::string GetText() const noexcept { return m_text; }

  ChapterType GetType() const noexcept { return m_chapter_type; }


  Option RequestOption(const std::vector<Option>& options) const;

  void SetObserver(Observer * const observer) const noexcept { m_observer = observer; }

  void SetVerbose(const bool verbose) const noexcept { m_verbose = verbose; }

  void ShowText(const std::string& text) const;
  void Wait() const;

  private:

  BallGameChapter m_ball_game_chapter;

  ///The text displayed at the end of the chapter
  std::string m_bye_text;

  ///When there is no choice
  Consequence m_consequence;

  const int m_chapter_number;

  ChapterType m_chapter_type;

  DiceGameChapter m_dice_game_chapter;

  FightingChapter m_fighting_chapter;

  GameLostChapter m_game_lost_chapter;

  GameWonChapter m_game_won_chapter;

  LuckChapter m_luck_chapter;

  mutable Observer * m_observer;

  OptionsChapter m_options_chapter;

  PawnShopChapter m_pawn_shop_chapter;

  PillGameChapter m_pill_game_chapter;

  ShopChapter m_shop_chapter;

  SkillChapter m_skill_chapter;

  std::string m_text;

  mutable bool m_verbose;

  void CharacterChanged(const Character& character) const;
};

std::ostream& operator<<(std::ostream& os, const Chapter& chapter);

#endif // CHAPTER_H
