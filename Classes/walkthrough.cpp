#include "walkthrough.h"

#include <cassert>
#include <iostream>

#include "game.h"
#include "helper.h"

Walkthrough::Walkthrough(
    const int seed,
    const Character& character
) : m_game(seed,character)
{
  m_game.SetObserver(this);
}

int Walkthrough::GetNumberOfCharsPerLine() const noexcept
{
#ifndef ARM9
  return 80;
#else
  return 32;
#endif
}

void Walkthrough::Start()
{
  while (1)
  {
    m_game.DoChapter();
    if (m_game.HasWon() || m_game.HasLost()) break;
  }
  assert(m_game.HasWon());
}

Option Walkthrough::RequestOption(const std::vector<Option>& options)
{
  for (const auto& option: options)
  {
    ShowText(" * " + option.GetText() + "\n");
  }
  assert(!options.empty());
  if (options.size() == 1) return options[0];
  if (options[0].GetConsequence().GetType() == ConsequenceType::no)
  {
    return options[0]; //Always say no
  }

  //If at [index], select option to go to [second]
  std::vector<int> solution(450,0);
  //Walk into city
  solution[  1] = 202; //Tell you want to be taken to Nicodemus
  solution[202] = 151; //Allow to be taken away
  solution[151] =  29; //Ignore the man
  solution[ 29] = 143; //Feign illness
  solution[143] = 306; //Keep feigning illness
  //At city square
  solution[ 74] =  95; //Walk west
  //Key street
  solution[ 95] = 300; //Walk past locksmith
  solution[300] = 347; //Pay gold
  solution[112] = 154; //Walk into house
  solution[154] =  13; //Pick up silver scorpion
  solution[ 13] = 273; //Pick up golden scorpion
  solution[273] = 334; //Leave the house
  solution[227] = 362; //Put on elven boots
  //Market street
  solution[287] = 413; //Walk past food stall
  solution[413] = 398; //Walk past musician
  solution[398] =  52; //Walk past ball game
  solution[200] = 117; //Walk past clairvoyant
  //Bridge street
  solution[117] =  31; //Walk past snakes
  solution[ 31] = 329; //Do not talk with man, go down bridge directly
  solution[329] = 238; //Walk down Candle street
  //Candle street
  solution[238] = 139; //Walk past pill game
  solution[139] = 375; //Walk past hags
  solution[375] =  40; //Climb over the wall
  solution[ 40] = 168; //Join the game
  //Harbour street
  solution[ 91] = 124; //Walk past beggar
  solution[124] = 180; //Walk past alley with dogs
  solution[180] =  34; //Avoid carriage with lord Azzur
  solution[171] = 399; //Board the ship
  solution[399] =  87; //Board the ship with rope ladder
  solution[ 87] =  50; //Sneak down
  solution[ 50] = 271; //Go in pirate crew cabin
  solution[271] = 162; //Cut pearls loose
  solution[  7] =  78; //Leave ship (with luck)
  solution[111] =  78; //Leave ship (without luck)
  solution[ 78] = 216; //Go into Clog street
  //Clog street
  solution[216] = 317; //Walk past ?goblin thief
  solution[317] = 280; //Walk past candle shop
  solution[280] = 213; //Enter Ben Borryman's shop
  solution[213] = 248; //Talk to Ben Borryman
  solution[248] =  85; //Pay in gold
  solution[100] = 246; //Enter Stable street
  //Stable street
  solution[246] = 363; //Ignore man
  solution[363] =  48; //Open manhole
  solution[ 48] = 321; //Climb down
  solution[321] = 356; //Go north
  solution[ 28] = 265; //Continue north
  solution[104] = 205; //Go back up
  solution[205] =  44; //Walk round the corner
  solution[372] = 131; //Enter serpent queen house
  solution[131] = 179; //Tell you are a tax collector
  solution[179] =  16; //Open the bag
  solution[ 76] =  25; //Enter barn
  solution[ 25] = 169; //Talk to blacksmith
  solution[169] =  46; //Buy chainmail coat
  solution[115] =  90; //Cut through chain
  solution[ 90] = 199; //Tell them you caught him
  solution[222] = 370; //Go into gardens
  solution[370] =  14; //Pluck the flower
  ///Mill Street
  solution[133] = 182; //Go down alley
  solution[182] = 279; //Buy tattoo
  solution[417] = 316; //Buy tattoo
  solution[307] = 290; //Walk past trolls
  solution[219] = 393; //Say no
  solution[393] = 156; //Merchant pass: allow to be kicked out
  solution[335] = 367; //No merchant pass: allow to be kicked out
  //Zanbar Bone's tower
  solution[259] =   4; //Ring the bell
  solution[  4] = 339; //Tell you are a lost traveller
  solution[339] =  77; //Explore the tower, go to second floor
  solution[ 77] = 310; //Go to third floor
  solution[310] =  65; //Go to the fourth floor
  solution[ 65] = 319; //Enter white door
  solution[319] = 352; //Open sarcophagus
  solution[352] = 106; //Throw the lantern
  solution[106] = 163; //Inspect the sarcophagus
  solution[231] =  96; //Enter black door
  solution[ 96] = 257; //Open the chest
  solution[244] = 337; //Use correct mixture

  const int chapter_number{
    m_game.GetCurrentChapterNumber()
  };

  //Special chapters
  if (chapter_number == 52)
  {
    ///Buy all needed
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetItemsToAdd().empty()) continue;
      assert(option.GetConsequence().GetItemsToAdd().size() == 1);
      if (option.GetConsequence().GetItemsToAdd()[0] == Item::lantern)
      {
        return option;
      }
      if (option.GetConsequence().GetItemsToAdd()[0] == Item::throwing_knife)
      {
        return option;
      }
    }
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetType() == ConsequenceType::leave)
      {
        return option;
      }
    }
  }

  //Special chapters
  if (chapter_number == 354)
  {
    ///Buy all needed
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetItemsToRemove().empty()) continue;
      assert(option.GetConsequence().GetItemsToRemove().size() == 1);
      if (option.GetConsequence().GetItemsToRemove()[0] == Item::eye_patch)
      {
        return option;
      }
      if (option.GetConsequence().GetItemsToRemove()[0] == Item::silver_flute)
      {
        return option;
      }
    }
    for (const auto& option: options)
    {
      if (option.GetConsequence().GetType() == ConsequenceType::leave)
      {
        return option;
      }
    }
  }


  if (solution[static_cast<size_t>(chapter_number)] == 0)
  {
    std::cerr << "Do not know where to go from chapter " << chapter_number << std::endl;
  }
  assert(solution[static_cast<size_t>(chapter_number)] != 0);
  const int target_chapter{solution[static_cast<size_t>(chapter_number)]};
  for (const auto& option: options)
  {
    if (option.GetConsequence().GetNextChapter() == target_chapter)
    {
      return option;
    }
  }
  assert(false);
  return options[1];
}

void Walkthrough::ShowText(const std::string& text)
{
  const std::string lines = Helper().StrToLines(text,GetNumberOfCharsPerLine());

  for (const char c: lines)
  {
    Helper().Cout(c);
    #ifndef ARM9
    std::cout.flush();
    #endif
  }
}

void Walkthrough::Wait()
{
  //Continue
}
