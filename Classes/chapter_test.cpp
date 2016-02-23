#ifndef NDEBUG
#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "chapter.h"
#include "terminal.h"

void Chapter::Test() noexcept
{
  {
    static bool is_tested{false};
    if (is_tested) return;
    is_tested = true;
  }

  const bool verbose{false};
  if (verbose) { std::clog << __func__ << std::endl; }

  Terminal d;
  d.SetAutoPlay(true);
  d.SetSilent(true);


  if (verbose) { std::clog << "Sequential fight" << std::endl; }
  {
    const Chapter chapter(5);
    assert(chapter.GetType() == ChapterType::fight);
    assert(chapter.GetFighting().DoFightSequentially());
    assert(chapter.GetFighting().GetMonsters().size() == 1);
    assert(chapter.GetFighting().GetMonsters()[0].GetAttackDamage() == 2);
    const std::string monster_name{chapter.GetFighting().GetMonsters()[0].GetName()};
    Character character(100,100,100,Item::luck_potion);
    assert(!character.HasFought(monster_name));

    d.ConnectTo(chapter);

    if (verbose) { std::clog << "Sequential fight, before do" << std::endl; }

    chapter.Do(character);

    if (verbose) { std::clog << "Sequential fight, after do" << std::endl; }

    assert(character.HasFought(monster_name));
  }
  if (verbose) { std::clog << "Chapter 326: Simulateous fight" << std::endl; }
  {
    const Chapter chapter(326);
    assert(!chapter.GetFighting().DoFightSequentially());
    assert(chapter.GetFighting().GetMonsters().size() == 2);
    Character character(100,100,100,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);

  }
  //Chapter 323: blacksmith must attack with attack strength 3
  {
    const Chapter chapter(323);
    assert(chapter.GetFighting().GetMonsters()[0].GetAttackDamage() == 3);
  }
  //Chapter 253: snakes must bite with attack strength 4
  {
    const Chapter chapter(253);
    assert(chapter.GetFighting().GetMonsters()[0].GetAttackDamage() == 4);
  }
  //Chapter 140: can escape after 3 rounds
  {
    const Chapter chapter(140);
    assert(chapter.GetFighting().GetRoundsToEscape() == 3);
    assert(chapter.GetFighting().GetEscapeToChapter() == 282);
  }
  //Chapter 9: Game over
  {
    const Chapter chapter(9);
    assert(chapter.GetType() == ChapterType::game_lost);
  }
  //Chapter 400: Game won
  {
    const Chapter chapter(400);
    assert(chapter.GetType() == ChapterType::game_won);
  }
  //Chapter 8: change status
  {
    const Chapter chapter(8);
    assert(chapter.GetConsequence().GetItemsToAdd().size() == 1);
    assert(chapter.GetConsequence().GetItemsToAdd()[0] == Item::golden_scorpion_brooch);
    assert(chapter.GetConsequence().GetChangeLuck() == 2);
  }
  //Chapter 26: no change of status
  {
    const Chapter chapter(26);
    assert(chapter.GetNextChapter() == 296);
  }
  //Chapter 206: dice game
  {
    const Chapter chapter(206);
    assert(chapter.GetType() == ChapterType::play_dice);
    assert(chapter.GetNextChapter() == 296);
    assert(!chapter.GetByeText().empty());
    Character character(100,100,100,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);

  }
  //Chapter 223: pill game
  {
    const Chapter chapter(223);
    assert(chapter.GetType() == ChapterType::play_pill);
    assert(chapter.GetNextChapter() == 165);
    assert(chapter.GetConsequence().GetChangeGold() == 20);
    assert(!chapter.GetByeText().empty());
    Character character(100,100,100,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);

  }
  //Chapter 378: ball game
  {
    const Chapter chapter(378);
    assert(chapter.GetType() == ChapterType::play_ball);
    assert(chapter.GetNextChapter() == 52);
    assert(!chapter.GetByeText().empty());
    Character character(100,100,100,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);

  }
  //Chapter 1: options
  {
    const Chapter chapter(1);
    assert(chapter.GetType() == ChapterType::normal);
    assert(chapter.GetOptions().GetOptions().size() == 3);
    Character character(100,100,100,Item::luck_potion);
    d.ConnectTo(chapter);
    chapter.Do(character);
  }
  //Chapter 3: option depending on gold
  {
    const Chapter chapter(3);
    assert(chapter.GetType() == ChapterType::normal);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 2);
    character.ChangeGold(-character.GetGold()); //Make player bankrupt
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
  }
  //Chapter 7: 2 options and status change
  {
    const Chapter chapter(7);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    assert(chapter.GetConsequence().GetItemsToAdd().size() == 1);
    assert(chapter.GetConsequence().GetItemsToAdd()[0] == Item::black_pearls);
    assert(chapter.GetConsequence().GetItemsToRemove().empty());
    Character character(10,10,10,Item::luck_potion);
    character.ChangeLuck(-character.GetLuck()); //Make player unlucky
    assert(character.GetLuck() == 0);
    assert(!character.HasItem(Item::black_pearls));

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(character.GetLuck() > 0);
    assert(character.HasItem(Item::black_pearls));
  }
  //Chapter 14: must respond to ring of fire
  {
    const Chapter chapter(14);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    assert(chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter() == 191);
    character.AddItem(Item::ring_of_fire);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    assert(chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter() == 237);
  }
  //Chapter 146: must respond to skeleton_key
  {
    const Chapter chapter(146);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int chapter_a{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    character.AddItem(Item::skeleton_key);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int chapter_b{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(chapter_a != chapter_b);
  }

  //Chapter 11: lose 1 skill point and shield
  {
    const Chapter chapter(11);
    Character character(10,10,10,Item::luck_potion);
    assert(character.HasItem(Item::shield));
    const int dex_before{character.GetSkill()};

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(!character.HasItem(Item::shield));
    const int dex_after{character.GetSkill()};
    assert(dex_after < dex_before); //Due to losing shield
    assert(!character.HasItem(Item::shield));
  }
  //Chapter 11: must lose shield
  {
    const Chapter chapter(11);
    Character character(10,10,10,Item::luck_potion);
    character.AddItem(Item::chainmail_coat);
    const int dex_before{character.GetSkill()};
    assert(character.HasItem(Item::shield));

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(!character.HasItem(Item::shield));
    const int dex_after{character.GetSkill()};
    assert(dex_after == dex_before - 1); //Due to losing shield
  }
  //Chapter 19: 2 options and status change
  {
    const Chapter chapter(19);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    Character character(10,10,10,Item::luck_potion);
    const int dex_before{character.GetSkill()};
    const int sta_before{character.GetCondition()};

    d.ConnectTo(chapter);
    chapter.Do(character);


    const int dex_after{character.GetSkill()};
    const int sta_after{character.GetCondition()};
    assert(dex_after == dex_before - 1);
    assert(sta_after == sta_before - 4);
  }
  //Chapter 15: Luck chapter must be parsed correctly
  {
    const Chapter chapter(15);
    assert(chapter.GetType() == ChapterType::test_your_luck);
    assert(!chapter.GetLuck().GetLuckText().empty());
    assert(!chapter.GetLuck().GetNoLuckText().empty());
    assert(chapter.GetLuck().GetLuckChapter() > 1);
    assert(chapter.GetLuck().GetNoLuckChapter() > 1);
  }
  //Chapter 15: Luck chapter must be parsed correctly
  {
    const Chapter chapter(15);
    assert(chapter.GetType() == ChapterType::test_your_luck);

    Character character(10,10,10,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(character.GetCurrentChapter() > -1);
  }
  //Chapter 18: Skill chapter must be parsed correctly
  {
    const Chapter chapter(18);
    assert(chapter.GetType() == ChapterType::test_your_skill);

    assert(!chapter.GetSkill().GetSkillText().empty());
    assert(!chapter.GetSkill().GetNoSkillText().empty());
    assert(chapter.GetSkill().GetSkillConsequence().GetNextChapter() == 102);
    assert(chapter.GetSkill().GetNoSkillConsequence().GetNextChapter() == 225);
  }
  //Chapter 18: Skill chapter must be parsed correctly
  {
    const Chapter chapter(18);
    Character character(10,10,10,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(character.GetCurrentChapter() > -1);
  }
  //Chapter 42: Must loose all provisions
  {
    const Chapter chapter(42);
    Character character(10,10,10,Item::luck_potion);
    assert(character.GetProvisions() > 0);

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(character.GetProvisions() == 0);
  }
  //Chapter 148: Lose one random items or one gold
  {
    const Chapter chapter(148);
    Character character(10,10,10,Item::luck_potion);
    const int n_items_before{static_cast<int>(character.GetItems().size())};
    const int gold_before{character.GetGold()};

    d.ConnectTo(chapter);
    chapter.Do(character);


    const int n_items_after{static_cast<int>(character.GetItems().size())};
    const int gold_after{character.GetGold()};
    assert(n_items_after == n_items_before - 1 || gold_after == gold_before - 1);
  }
  //Chapter 63: Lose two random items
  {
    const Chapter chapter(63);
    Character character(10,10,10,Item::luck_potion);
    const int n_items_before{static_cast<int>(character.GetItems().size())};

    d.ConnectTo(chapter);
    chapter.Do(character);


    const int n_items_after{static_cast<int>(character.GetItems().size())};
    assert(n_items_after == n_items_before - 2);
  }

  //Chapter 134: Lose all gold
  {
    const Chapter chapter(134);
    Character character(10,10,10,Item::luck_potion);
    assert(character.GetGold() > 0);

    d.ConnectTo(chapter);
    chapter.Do(character);


    assert(character.GetGold() == 0);
  }

  //Chapter 264: option depending on provisions
  {
    const Chapter chapter(264);
    assert(chapter.GetType() == ChapterType::normal);
    assert(chapter.GetOptions().GetOptions().size() == 2);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 2);
    character.ChangeProvisions(-character.GetProvisions()); //Make player bankrupt
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
  }
  //Chapter 239: all_needed_to_slay_zanbar_bone
  {
    const Chapter chapter(239);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_all_chapter_1{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    character.AddItem(Item::tattoo);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_all_chapter_2{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_all_chapter_1 == not_all_chapter_2);
    character.AddItem(Item::hags_hair);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_all_chapter_3{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_all_chapter_1 == not_all_chapter_3);
    character.AddItem(Item::lotus_flower);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_all_chapter_4{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_all_chapter_1 == not_all_chapter_4);
    character.AddItem(Item::black_pearls);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_all_chapter_5{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_all_chapter_1 == not_all_chapter_5);
    character.AddItem(Item::silver_arrow);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int all_chapter{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_all_chapter_1 != all_chapter);

  }
  //Chapter 53: Can only give if something silver, with direct consequence
  {
    const Chapter chapter(53);
    Character character(10,10,10,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    character.AddItem(Item::silver_arrow);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 2);

    d.ConnectTo(chapter);
    chapter.Do(character);


    //WHat is the test?
  }
  //Chapter 80: any_scorpion_brooch
  {
    const Chapter chapter(80);
    Character character(1,1,1,Item::luck_potion);
    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_chapter{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    character.AddItem(Item::copper_scorpion_brooch);
    const int yes_chapter_1{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_chapter != yes_chapter_1);
    character.RemoveItem(Item::copper_scorpion_brooch);
    character.AddItem(Item::silver_scorpion_brooch);
    const int yes_chapter_2{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_chapter != yes_chapter_2);
    character.RemoveItem(Item::silver_scorpion_brooch);
    character.AddItem(Item::golden_scorpion_brooch);
    const int yes_chapter_3{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_chapter != yes_chapter_3);
    assert(yes_chapter_1 == yes_chapter_3);
    assert(yes_chapter_2 == yes_chapter_3);
  }

  //Chapter 36: shop chapter
  {
    const Chapter chapter(36);
    assert(chapter.GetType() == ChapterType::shop);
    assert(chapter.GetShop().GetItems().size() > 0);
    assert(!chapter.GetByeText().empty());
    Character character(100,100,100,Item::luck_potion);
    const int n_items_before{static_cast<int>(character.GetItems().size())};

    d.ConnectTo(chapter);
    chapter.Do(character); //Buy everything


    const int n_items_after{static_cast<int>(character.GetItems().size())};
    assert(n_items_after > n_items_before);
  }

  //Chapter 354: pawn shop chapter
  {
    const Chapter chapter(354);
    assert(chapter.GetType() == ChapterType::pawn_shop);
    assert(!chapter.GetByeText().empty());
    Character character(100,100,100,Item::luck_potion);
    const int n_items_before{static_cast<int>(character.GetItems().size())};
    character.AddItem(Item::knucklebones); //Add one item, which must be pawned

    d.ConnectTo(chapter);
    chapter.Do(character);


    const int n_items_after_again{static_cast<int>(character.GetItems().size())};
    assert(n_items_after_again == n_items_before); //Sold everything
  }

  //Chapter 431: fight random monster
  {
    const Chapter chapter(431);
    assert(chapter.GetType() == ChapterType::fight);
    Character character(100,100,100,Item::luck_potion);

    d.ConnectTo(chapter);
    chapter.Do(character);

  }


  //Chapter 392: Lizardine has fiery breath
  {
    const Chapter chapter(392);
    assert(chapter.GetFighting().GetMonsters().size() == 1);
    assert(chapter.GetFighting().GetMonsters()[0].HasFireBreath());
  }

  //Chapter 190: test-your-skill for skilled character
  {
    const Chapter chapter(190);
    assert(chapter.GetType() == ChapterType::test_your_skill);
    assert(chapter.GetSkill().GetSkillConsequence().GetNextChapter() == 38);
    Character character(100,100,100,Item::luck_potion);
    d.ConnectTo(chapter);
    chapter.Do(character);
    assert(character.GetCurrentChapter() == 38);
  }
  //Chapter 190: test-your-skill for unskilled character
  {
    const Chapter chapter(190);
    assert(chapter.GetType() == ChapterType::test_your_skill);
    assert(chapter.GetSkill().GetNoSkillConsequence().GetNextChapter() == 296);
    Character character(1,1,1,Item::luck_potion);
    const int gold_before{character.GetGold()};

    d.ConnectTo(chapter);
    chapter.Do(character);

    const int gold_after{character.GetGold()};
    assert(gold_after < gold_before);
    assert(character.GetCurrentChapter() == 296);
  }

  //Chapter 297: must respond to monster being faught
  {
    const Chapter chapter(297);
    Character character(100,100,100,Item::luck_potion);

    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int not_fought_chapter{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter() == 207);

    const Chapter fight_chapter(207);

    d.ConnectTo(fight_chapter);
    fight_chapter.Do(character);


    const std::string s{character.ShowInventory()};
    assert(!s.empty());
    assert(character.HasFought("second_death_hawk"));
    assert(character.HasFought("first_death_hawk"));

    assert(chapter.GetOptions().GetValidOptions(character).size() == 1);
    const int yes_fought_chapter{chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter()};
    assert(not_fought_chapter != yes_fought_chapter);
    assert(chapter.GetOptions().GetValidOptions(character)[0].GetNextChapter() == 65);
  }

  //Chapter 343: Lose all silver items
  {
    const Chapter chapter(343);
    Character character(10,10,10,Item::luck_potion);
    character.AddItem(Item::silver_arrow);
    character.AddItem(Item::silver_chalice);
    character.AddItem(Item::silver_flute);
    character.AddItem(Item::silver_insect_bracelet);
    character.AddItem(Item::silver_scorpion_brooch);
    character.AddItem(Item::silver_spoon);
    character.AddItem(Item::two_silver_goblets);
    character.AddItem(Item::ivory_skull_on_a_silver_chain);

    d.ConnectTo(chapter);
    chapter.Do(character);

    assert(!character.HasItem(Item::silver_arrow));
    assert(!character.HasItem(Item::silver_chalice));
    assert(!character.HasItem(Item::silver_flute));
    assert(!character.HasItem(Item::silver_insect_bracelet));
    assert(!character.HasItem(Item::silver_scorpion_brooch));
    assert(!character.HasItem(Item::silver_spoon));
    assert(!character.HasItem(Item::two_silver_goblets));
    assert(!character.HasItem(Item::ivory_skull_on_a_silver_chain));
  }

  //Silver scorpion brooch must not revive
  {
    const Chapter chapter(403); //Fatnose fight
    Character character(1,1,1,Item::luck_potion);
    character.AddItem(Item::silver_scorpion_brooch);

    d.ConnectTo(chapter);
    chapter.Do(character);

    //Character is dead unless silver scorpion brooch resurrected him/her
    assert(character.IsDead());
  }
  //Parse chapters using Chapter
  {
    std::ofstream f("TODO.txt");
    for (int i=1; i!=450; ++i)
    {
      try
      {
        const Chapter chapter(i);
        if (chapter.GetNextChapter() == 1)
        {
          f << i << ": incorrect Next_chapter" << std::endl;
        }
        else
        {
          //f << i << ": OK" << std::endl;
        }
      }
      catch (std::logic_error& e)
      {
        f << i << ": FAIL" << std::endl;
      }
      catch (std::runtime_error& e)
      {
        //f << i << ": not present" << std::endl;
      }
    }
  }

  //Try all chapters
  for (int i=1; i!=450; ++i)
  {
    try
    {
      Character character(100,100,100,Item::luck_potion);
      switch (i)
      {
        case 2: character.AddItem(Item::silver_insect_bracelet); break;
        case 55: character.AddItem(Item::gold_flower); break;
        case 106: character.AddItem(Item::lantern); break;
        case 157: character.RemoveItem(Item::carralifs_sword); character.RemoveItem(Item::shield); break;
        case 172: character.AddItem(Item::gold_flower); break;
        case 230: character.RemoveItem(Item::carralifs_sword); character.RemoveItem(Item::shield); break;
        case 240: character.AddItem(Item::two_gems); break;
        case 306: character.RemoveItem(Item::carralifs_sword); character.RemoveItem(Item::shield); break;
        case 351: character.RemoveItem(Item::carralifs_sword); character.RemoveItem(Item::shield); break;
        case 423: character.RemoveItem(Item::carralifs_sword); break;
      }
      std::cout << "CHAPTER " << i << std::endl;
      Chapter chapter(i);
      d.ConnectTo(chapter);
      chapter.Do(character);
    }
    catch (std::runtime_error& e)
    {
      std::cout << e.what() << std::endl;
    }
    catch (std::logic_error& e)
    {
      std::cout << e.what() << std::endl;
    }
  }
}
#endif

