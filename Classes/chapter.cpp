#include "chapter.h"

#include <cassert>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ai.h"
#include "dice.h"
#include "getfile.h"
#include "helper.h"

Chapter::Chapter(const int chapter_number)
  :
    m_ball_game_chapter{*this},
    m_bye_text{},
    m_consequence{},
    m_chapter_number{chapter_number},
    m_chapter_type{ChapterType::normal},
    m_dice_game_chapter{*this},
    m_fighting_chapter{FightingChapter(*this)},
    m_game_lost_chapter{this},
    m_game_won_chapter{this},
    m_luck_chapter(*this),
    m_observer{nullptr},
    m_options_chapter{},
    m_pawn_shop_chapter(this),
    m_pill_game_chapter{*this},
    m_shop_chapter{this},
    m_skill_chapter{*this},
    m_text{},
    m_verbose{false}
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
  Helper h;

  if (m_verbose) { std::clog << __func__ << std::endl; }

  #ifdef USE_TEXT_FILES_FOR_INPUT
  const std::string filename{h.GetFilesFolder() + h.ToStr(chapter_number) + ".txt"};
  if (!h.IsRegularFile(filename))
  {
    std::stringstream msg;
    msg << __func__ << ": ERROR: File " << filename << " does not exist";
    Helper().Cout(msg.str());
    throw std::runtime_error(msg.str());
  }
  const std::vector<std::string> lines{h.FileToVector(filename)};
  #else
  const std::vector<std::string> lines(1,GetFile(h.ToStr(chapter_number)));
  #endif
  std::stringstream s;
  std::copy(std::begin(lines),std::end(lines),std::ostream_iterator<std::string>(s," "));

  m_text = h.ReadText(s);

  m_chapter_type = ReadChapterType(s);

  switch (m_chapter_type)
  {
    case ChapterType::game_lost: return;
    case ChapterType::game_won: return;
    default: break;
  }

  while (!s.eof())
  {
    const std::string str{h.ReadString(s)};
    if (str.empty())
    {
      break;
    }
    else if (str == "Bye" || str == "bye")
    {
      m_bye_text = h.ReadText(s);
    }
    else if (str == "Change" || str == "change")
    {
      m_consequence.Add(ParseConsequence(s));
    }
    else if (str == "Escape" || str == "escape")
    {
      GetFighting().SetRoundsToEscape(h.ReadInt(s));
      GetFighting().SetEscapeToChapter(h.ReadInt(s));
    }
    else if (str == "Fight_both" || str == "fight_both")
    {
      GetFighting().SetFightSequentially(false);
    }
    else if (str == "Luck" || str == "luck")
    {
      assert(this->m_chapter_type == ChapterType::test_your_luck);
      const std::string luck_text{h.ReadText(s)};
      assert(!luck_text.empty());
      GetLuck().SetLuckText(luck_text);
      const std::string goto_str{h.ReadString(s)};
      assert(goto_str == "goto");
      const int luck_chapter{h.ReadInt(s)};
      assert(luck_chapter > 1);
      GetLuck().SetLuckChapter(luck_chapter);
    }
    else if (str == "Monster" || str == "monster")
    {
      this->m_chapter_type = ChapterType::fight;
      const Monster monster{ParseMonster(s)};
      GetFighting().AddMonster(monster);
    }
    else if (str == "Next_chapter" || str == "goto")
    {
      m_consequence.SetNextChapter(h.ReadInt(s));
    }
    else if (str == "No_luck" || str == "no_luck")
    {
      assert(this->m_chapter_type == ChapterType::test_your_luck);
      //s << std::noskipws; //Obligatory
      //Parse(s,' '); //You expect a space after a word
      const std::string no_luck_text{h.ReadText(s)};
      assert(!no_luck_text.empty());
      GetLuck().SetNoLuckText(no_luck_text);
      const std::string then{h.ReadString(s)};
      if (then == "change")
      {
        const Consequence no_luck_consequence{ParseConsequence(s)};
        GetLuck().SetNoLuckConsequence(no_luck_consequence);
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
      }
      else
      {
        assert(then == "goto");
      }
      const int no_luck_chapter{h.ReadInt(s)};
      assert(no_luck_chapter > 1);
      GetLuck().SetNoLuckChapter(no_luck_chapter);
    }
    else if (str == "No_skill" || str == "no_skill")
    {
      assert(this->m_chapter_type == ChapterType::test_your_skill);
      //Parse(s,' '); //You expect a space after a word
      const std::string no_skill_text{h.ReadText(s)};
      assert(!no_skill_text.empty());
      GetSkill().SetNoSkillText(no_skill_text);
      const std::string then_str{h.ReadString(s)};
      Consequence consequence;
      if (then_str == "goto")
      {
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else if (then_str == "change")
      {
        consequence = ParseConsequence(s);
        //Also read goto
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else
      {
        assert(!"Should not get here");
      }
      GetSkill().SetNoSkillConsequence(consequence);
    }
    else if (str == "Option" || str == "option")
    {
      const std::string option_text{h.ReadText(s)};
      const std::string t{h.ReadString(s)};
      if (t == "if")
      {
        const Condition condition{ParseCondition(s)};

        const std::string then_str{h.ReadString(s)};
        Consequence consequence;
        if (then_str == "goto")
        {
          consequence.SetNextChapter(h.ReadInt(s));
        }
        else if (then_str == "change")
        {
          consequence = ParseConsequence(s);
          //Also read goto
          const std::string goto_str{h.ReadString(s)};
          assert(goto_str == "goto");
          consequence.SetNextChapter(h.ReadInt(s));
        }
        else
        {
          assert(!"Should not get here");
        }
        Option option(option_text,consequence);
        option.SetCondition(condition);
        GetOptions().AddOption(option);
      }
      else if (t == "ifnot")
      {
        Condition condition;
        const std::string what{h.ReadString(s)};
        if (IsItem(what))
        {
          const Item item_not_needed{ToItem(what)};
          condition.AddItemNotNeeded(item_not_needed);
        }
        else
        {
          std::cerr << "Unknown item " << what << " in chapter " << chapter_number << std::endl;
          assert(!"Should not get here");
        }
        const std::string str_goto{h.ReadString(s)};
        assert(str_goto == "goto");
        Consequence consequence;
        consequence.SetNextChapter(h.ReadInt(s));
        Option option(option_text,consequence);
        option.SetCondition(condition);
        GetOptions().AddOption(option);
      }
      else if (t == "goto")
      {
        Consequence consequence;
        consequence.SetNextChapter(h.ReadInt(s));
        const Option option(option_text,consequence);
        GetOptions().AddOption(option);
      }
      else if (h.IsInt(t))
      {
        std::clog << "WARNING: goto omitted in chapter " << chapter_number << std::endl;
        //If no goto, just parse the number
        Consequence consequence;
        consequence.SetNextChapter(h.ToInt(t));
        const Option option(option_text,consequence);
        GetOptions().AddOption(option);
      }
      else
      {
        std::cerr << "Unknown option " << t << " in chapter " << chapter_number <<std::endl;
        assert(!"Should not get here");
      }
    }
    else if (str == "Random_monsters" || str == "random_monsters")
    {
      std::vector<Monster> monsters{ParseMonsters(s)};
      m_chapter_type = ChapterType::fight;
      const int which_monster_index{Dice::Get()->Throw() - 1};
      assert(which_monster_index >= 0);
      assert(which_monster_index < static_cast<int>(monsters.size()));
      const Monster monster{monsters[which_monster_index]};
      m_fighting_chapter.AddMonster(monster);
    }
    else if (str == "Sell_items" || str == "sell_items")
    {
      assert(this->m_chapter_type == ChapterType::pawn_shop);
      //m_chapter_type = ChapterType::pawn_shop;
      m_pawn_shop_chapter = ParsePawnShopChapter(s,this);
    }
    else if (str == "Shop_items" || str == "shop_items")
    {
      assert(this->m_chapter_type == ChapterType::shop);
      //m_chapter_type = ChapterType::shop;
      m_shop_chapter = ParseShopChapter(s,this);
    }
    else if (str == "Skill" || str == "skill")
    {
      assert(this->m_chapter_type == ChapterType::test_your_skill);
      this->m_chapter_type = ChapterType::test_your_skill;
      //Parse(s,' '); //You expect a space after a word
      const std::string skill_text{h.ReadText(s)};
      assert(!skill_text.empty());
      GetSkill().SetSkillText(skill_text);
      const std::string then_str{h.ReadString(s)};
      Consequence consequence;
      if (then_str == "goto")
      {
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else if (then_str == "change")
      {
        consequence = ParseConsequence(s);
        //Also read goto
        const std::string goto_str{h.ReadString(s)};
        assert(goto_str == "goto");
        consequence.SetNextChapter(h.ReadInt(s));
      }
      else
      {
        assert(!"Should not get here");
      }
      GetSkill().SetSkillConsequence(consequence);

    }

    else
    {
      std::cerr
        << "Chapter cannot parse chapter " << chapter_number  << '\n'
        << "Unknown string: " << str << '\n'
      ;
      assert(!"Should not get here");
    }
  }

}

void Chapter::Do(Character& character) const
{
  if (m_verbose) { std::clog << __func__ << std::endl; }
  Helper h;

  assert(m_observer);
  character.SetObserver(m_observer);

  if (m_verbose) { std::clog << "The first text comes now" << std::endl; }

  ShowText("\n");

  #ifndef NDEBUG
  ShowText("CHAPTER " + h.ToStr(GetChapterNumber()) + "\n");
  #endif

  //Display the text line by line
  ShowText(m_text + "\n");

  if (m_verbose) { std::clog << "The first text has been" << std::endl; }


  if (GetType() == ChapterType::game_lost)
  {
    m_game_lost_chapter.Do(character);
    assert(character.IsDead());
    return;
  }
  else if (GetType() == ChapterType::game_won)
  {
    ShowText("\n");
    m_game_won_chapter.Do(character);
    ShowText("\n");
    return;
  }
  else if (GetType() == ChapterType::play_dice)
  {
    m_dice_game_chapter.Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::play_ball)
  {
    m_ball_game_chapter.Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::play_pill)
  {
    m_pill_game_chapter.Do(character);
    if (character.IsDead()) return;
    m_consequence.Apply(character);
  }
  //Options
  else if (!GetOptions().GetOptions().empty())
  {
    if (GetOptions().GetValidOptions(character).empty())
    {
      std::cerr
        << "ERROR: no valid options in chapter " << character.GetCurrentChapter()
        << std::endl
        << "Options:\n"
      ;
      assert(GetOptions().GetOptions().size() == 2);
    }
    while (1)
    {
      if (m_verbose) { std::clog << "Let the use choose a valid option" << std::endl; }

      auto options = GetOptions().GetValidOptions(character);

      //If there are options, add (1) showing inventory (2) eating provision (3) drinking potion
      if (options.size() > 1)
      {
        //Add to show the inventory
        options.push_back(CreateShowInventoryOption());
        if (character.GetProvisions() > 0) { options.push_back(CreateEatProvisionOption()); }
        if (character.HasPotion()) { options.push_back(CreateDrinkPotionOption()); }
      }

      if (m_verbose) { std::clog << "Do the request" << std::endl; }

      assert(m_observer);
      const auto chosen = m_observer->RequestOption(options);

      if (m_verbose) { std::clog << "Done the request" << std::endl; }

      ShowText("\n");
      if (chosen.GetConsequence().GetType() == ConsequenceType::show_inventory)
      {
        //Showing the inventory is trivial
        this->ShowText(character.ShowInventory());
        continue;
      }
      if (chosen.GetConsequence().GetType() == ConsequenceType::eat_provision)
      {
        character.ChangeProvisions(-1);
        character.ChangeCondition(4);
        continue;
      }
      if (chosen.GetConsequence().GetType() == ConsequenceType::drink_potion)
      {
        character.DrinkPotion();
        continue;
      }

      chosen.DoChoose(character);
      assert(m_consequence.GetNextChapter() == -1);

      //Only apply these consequences once
      m_consequence.Apply(character);
      break;
    }
  }
  else if (GetType() == ChapterType::fight)
  {
    const int n_chapters_before{static_cast<int>(character.GetChapters().size())};
    m_fighting_chapter.Do(character);
    if (character.IsDead())
    {
      m_game_lost_chapter.Do(character);
      return;
    }

    assert(m_consequence.GetNextChapter() > 0);
    const int n_chapters_after{static_cast<int>(character.GetChapters().size())};
    if (n_chapters_after != n_chapters_before)
    {
      //Player has escaped
      //Check that there are no other consequences that need to be applied
      assert(m_consequence.GetChangeArrows() == 0);
      assert(m_consequence.GetChangeCondition() == 0);
      assert(m_consequence.GetChangeGold() == 0);
      assert(m_consequence.GetChangeLuck() == 0);
      assert(m_consequence.GetChangeProvisions() == 0);
      assert(m_consequence.GetChangeSkill() == 0);
      assert(m_consequence.GetItemsToAdd().empty());
      assert(m_consequence.GetItemsToRemove().empty());
    }
    else
    {
      m_consequence.Apply(character);
    }
  }
  else if (GetType() == ChapterType::test_your_luck)
  {
    GetLuck().Do(character);
  }
  else if (GetType() == ChapterType::test_your_skill)
  {
    GetSkill().Do(character);
  }
  else if (GetType() == ChapterType::shop)
  {
    GetShop().Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::pawn_shop)
  {
    GetPawnShop().Do(character);
    m_consequence.Apply(character);
  }
  else if (GetType() == ChapterType::normal)
  {
    //Nothing
    m_consequence.Apply(character);
  }
  else
  {
    assert(!"Should not get here");
  }

  if (character.IsDead())
  {
    m_game_lost_chapter.Do(character);
    return;
  }

  ShowText(m_bye_text);
}


Option Chapter::RequestOption(const std::vector<Option>& options) const
{
  assert(m_observer);
  return m_observer->RequestOption(options);
}

void Chapter::ShowText(const std::string& text) const
{
  if (m_verbose) { Helper().CoutNl(__func__); }

  assert(m_observer);
  m_observer->ShowText(text);
}

std::string SummarizeChapter(const int chapter_number)
{
  switch (chapter_number)
  {
    case 1: return "Before gate";
    case 2: return "Use insect bracelet";
    case 3: return "Singer";
    case 4: return "Servant";
    case 6: return "She is annoyed";
    case 7: return "Got pearls";
    case 8: return "Bought golden scorpion brooch";
    case 9: return "Game over";
    case 11: return "Run to tree";
    case 12: return "Hide";
    case 13: return "Get silver scorpion brooch";
    case 14: return "Could use ring of fire";
    case 16: return "Get loot";
    case 17: return "Man in rags";
    case 19: return "Hit by darts";
    case 20: return "Get stale bread";
    case 21: return "In bedroom";
    case 24: return "Outside jeweller";
    case 25: return "In stable";
    case 26: return "Won pubfight";
    case 27: return "May play deadly game";
    case 28: return "Fought the rats";
    case 29: return "On matrass";
    case 30: return "Halfway Stable Street";
    case 31: return "On the Catfish Bridge";
    case 32: return "She bites";
    case 33: return "Try to sell chalices";
    case 34: return "Carriage passes";
    case 35: return "Deal with spirit stalker";
    case 36: return "Buying rings";
    case 37: return "Get 2 luck from song";
    case 38: return "Get insect bracelet";
    case 39: return "Panicking";
    case 40: return "Bays ball";
    case 41: return "Paid the bribe";
    case 42: return "Get the silver arrow";
    case 43: return "Goblet C hurts";
    case 44: return "May throw a knife";
    case 45: return "Winged helmet";
    case 46: return "Get chainmail";
    case 47: return "Hit by lightning";
    case 48: return "On iron ladder";
    case 50: return "Cargo hold";
    case 51: return "Offered a drink";
    case 52: return "Buying weapons";
    case 53: return "Woman wants silver";
    case 54: return "Got merchant pass";
    case 55: return "Petals turn to gold";
    case 56: return "Imprisoned forever";
    case 58: return "Whipped from carriage";
    case 59: return "The hag kills you";
    case 60: return "You are discovered";
    case 61: return "Serpent queen";
    case 62: return "Inside Spotted Dog";
    case 63: return "The elf steals";
    case 65: return "Fourth floor";
    case 66: return "May buy skeleton key";
    case 67: return "Who sent it";
    case 68: return "Disgusting soup";
    case 70: return "Zanbar Bone kills you";
    case 71: return "Find a box";
    case 74: return "First junction";
    case 75: return "The rain has stopped";
    case 76: return "Outside a barn";
    case 77: return "Second floor";
    case 78: return "Halfway Harbor Street";
    case 79: return "She bites";
    case 80: return "Meeting with owner";
    case 82: return "Get hag hair";
    case 83: return "The effect is random";
    case 84: return "The barrels are empty";
    case 85: return "Get silver arrow";
    case 86: return "Find small glass ball";
    case 87: return "On the deck";
    case 88: return "She bites";
    case 89: return "The glove is cursed";
    case 90: return "The chain is stronger";
    case 91: return "Beggar";
    case 92: return "Get mirror";
    case 93: return "Outside Spotted Dog";
    case 94: return "Receive healing";
    case 95: return "Outside locksmith";
    case 96: return "Room behind black door";
    case 97: return "Get iron key";
    case 98: return "The liquid is good";
    case 100: return "Fourth junction";
    case 101: return "No refund";
    case 102: return "The vagabonds retreat";
    case 103: return "End of first split";
    case 104: return "Entrance hole of sewers";
    case 105: return "Before house with kennel";
    case 106: return "Mummy is dead";
    case 107: return "Wooden chest";
    case 108: return "Outside the City";
    case 109: return "Bribe is not accepted";
    case 110: return "You beat Sourbelly";
    case 111: return "Get Black Pearls";
    case 112: return "Outside red house";
    case 113: return "Two squabbling old women";
    case 114: return "Loot all rings and 53 gold";
    case 115: return "Meet escapee";
    case 116: return "Outside herbalist shop";
    case 117: return "Rain outside derelict house";
    case 118: return "May use insect bracelet";
    case 119: return "May buy drink";
    case 121: return "No thanks from ogre";
    case 122: return "Two men with sticks";
    case 123: return "Get skeleton key";
    case 124: return "In front of alleyway";
    case 125: return "The shield is cursed";
    case 126: return "You are healed";
    case 127: return "Harassment";
    case 129: return "Wrong choice";
    case 131: return "Woman voice asks";
    case 132: return "Buy silver scorpion brooch";
    case 133: return "May buy fruit";
    case 134: return "All gold lost";
    case 135: return "Threated with an egg";
    case 136: return "Talk to innkeeper";
    case 137: return "Arrows flying in";
    case 138: return "Have you fought the ape man";
    case 139: return "Outside house with arguing voices";
    case 141: return "May drink soup";
    case 142: return "The poison is deadly";
    case 143: return "Feigning illness";
    case 145: return "May buy flowers";
    case 146: return "May use skeleton key";
    case 147: return "16 gold and green liquid";
    case 148: return "Loose 1 gold or item";
    case 149: return "Poison damage";
    case 150: return "There is no Pepper Street";
    case 151: return "In jail";
    case 152: return "Pirate fight";
    case 153: return "The golden owls saves you";
    case 154: return "Room with tables";
    case 155: return "Trampled";
    case 156: return "Outside the city";
    case 158: return "Escape the armour";
    case 159: return "In posh house";
    case 160: return "May buy from boy";
    case 161: return "Outside ogre house";
    case 163: return "Got Ring of the Golden Eye";
    case 164: return "Stagger forward";
    case 165: return "Leave the six skull house";
    case 167: return "Buy herbs";
    case 169: return "May buy chainmail";
    case 171: return "In front of pirate ship";
    case 172: return "Give golden flower";
    case 173: return "May join game";
    case 174: return "Back at sewer entrance";
    case 176: return "Talking to pirate";
    case 178: return "In ogre second room";
    case 179: return "Find bag";
    case 180: return "Carriage approaches";
    case 181: return "The key fits";
    case 182: return "May buy tattoo";
    case 183: return "May buy mixture";
    case 184: return "May use golden flower";
    case 185: return "Armour is harmless";
    case 186: return "May pick up copper scorpion brooch";
    case 187: return "May bribe guards";
    case 188: return "See snakes";
    case 189: return "Defeated stalker";
    case 193: return "May use ring of fire";
    case 194: return "Get glass ball";
    case 195: return "Tell which person";
    case 196: return "End of first split";
    case 197: return "Fifth floor";
    case 198: return "Get ivory skull";
    case 199: return "Get 5 gold as reward";
    case 200: return "Outside clairvoyant";
    case 201: return "Letter from Nicodemus";
    case 202: return "Taken prisoner";
    case 204: return "Scorpion scurries away";
    case 205: return "Eery silence";
    case 208: return "Get 2 gold and garlic and knucklebones";
    case 209: return "Get 12 gold";
    case 211: return "Eat plum";
    case 212: return "No more guards";
    case 213: return "Meet silversmith";
    case 215: return "May buy scorpion brooches";
    case 216: return "Small boy";
    case 218: return "Get info";
    case 219: return "A trick question";
    case 220: return "Get 2 silver goblets and chalice and spoon";
    case 221: return "Ambushed";
    case 222: return "Outside gardens";
    case 224: return "Talk to dwarf";
    case 227: return "Find boots";
    case 228: return "Beautiful hallway";
    case 230: return "Escape using hidden key";
    case 231: return "Outside landing fourth floor";
    case 232: return "Room with tub";
    case 233: return "Slightly refreshing";
    case 234: return "Advice and find Zanbar Bone";
    case 235: return "Crawl out";
    case 236: return "Relationship with Nicodemus";
    case 237: return "Use jewel and get lotus flower";
    case 238: return "Outside house with 6 skulls";
    case 239: return "Escape out of town";
    case 240: return "Gems sold and may buy rings";
    case 241: return "May buy coloured candle";
    case 242: return "Apple is sour";
    case 243: return "Feigning death and escape";
    case 244: return "Choose compound";
    case 245: return "In ogre first room";
    case 246: return "May buy drink";
    case 247: return "Ambush";
    case 248: return "May buy silver arrow";
    case 250: return "Meet half orc";
    case 254: return "Use garlic and escape to next floor";
    case 255: return "Passed";
    case 256: return "May talk to fisherwomen";
    case 257: return "May use Ring of the Golden Eye";
    case 258: return "May use ivory skull";
    case 259: return "Outside tower";
    case 260: return "Bribe accepted";
    case 261: return "Advice";
    case 262: return "Leave the house";
    case 263: return "May use Golden Owl";
    case 264: return "Ogre asks food";
    case 265: return "May use Potion of Mind Control";
    case 266: return "Lost the match";
    case 267: return "Bribe accepted";
    case 268: return "Panic";
    case 269: return "Little man missed";
    case 271: return "Three sleeping pirates";
    case 272: return "See iron grill";
    case 273: return "Wear golden scorpion brooch";
    case 274: return "Reward of 5 gold pieces";
    case 275: return "Carriage has passed";
    case 276: return "Bribe";
    case 277: return "Run away";
    case 278: return "Table with goblets";
    case 279: return "Get tattoo";
    case 280: return "Outside silversmith";
    case 281: return "Before dark room";
    case 282: return "Small boy";
    case 283: return "No loot";
    case 284: return "Leave pirates";
    case 285: return "Find 7 gold and white bread and set of keys";
    case 286: return "Mummy dies by ring";
    case 287: return "Food stall";
    case 288: return "Killed in your sleep";
    case 289: return "Orc knows nothing";
    case 290: return "Trolls ask for pass";
    case 292: return "May use garlic";
    case 293: return "May buy flowers";
    case 294: return "Encounter with pirate";
    case 295: return "Get 12 gold pieces and 1 luck";
    case 297: return "Leave room";
    case 298: return "Poison hurts";
    case 299: return "Mission failed";
    case 300: return "Threat";
    case 301: return "Find battle axe in armour";
    case 302: return "Gems sold for 9 gold pieces";
    case 303: return "Get hags hair";
    case 304: return "End of first split";
    case 305: return "Stalker is unaffected";
    case 306: return "Guards flee and get merchant pass";
    case 307: return "See elite guard";
    case 308: return "Nothing here";
    case 310: return "Third floor";
    case 311: return "Reinforcements arrive";
    case 312: return "Get Golden Owl";
    case 313: return "Done";
    case 314: return "Free little man";
    case 315: return "May buy one brooch";
    case 316: return "Back at tattooist";
    case 317: return "Outside candle maker";
    case 318: return "Leave unharmed";
    case 319: return "See sarcophagus";
    case 320: return "A friendly talk";
    case 321: return "At the bottom of the ladder";
    case 322: return "Loot 11 gold pieces";
    case 324: return "Get two gems and 15 gold pieces and glove";
    case 325: return "A refreshing drink at Hog and Frog";
    case 327: return "Staggering to girl";
    case 328: return "Thanked with two gold";
    case 329: return "Nicodemus";
    case 330: return "Hurt by bolt";
    case 332: return "1 luck";
    case 333: return "End of split";
    case 334: return "Guards ask merchant pass";
    case 335: return "Pay all gold or be arrested";
    case 336: return "Inside jewellers shop";
    case 337: return "The right choice";
    case 338: return "Drank potion of misfortune";
    case 339: return "First floor";
    case 340: return "Get magnificent shield and 25 gold and 1 luck";
    case 341: return "Run after sprinkling 5 gold";
    case 342: return "May buy advice";
    case 343: return "Unconcious";
    case 344: return "Make way for Lord Azzur";
    case 345: return "May accept offer";
    case 346: return "Lethal fall";
    case 347: return "Lose ten gold";
    case 348: return "See small cloaked people";
    case 350: return "Start to panic";
    case 351: return "The man helps you escape for 10 gold";
    case 352: return "Encounter mummy and may use lantern";
    case 353: return "Door is locked";
    case 354: return "Pawn shop";
    case 355: return "Dash into the city";
    case 358: return "On the city walls";
    case 359: return "Won match and get Potion of Mind Control";
    case 360: return "Wraggins runs away";
    case 362: return "Get magic elven boots";
    case 363: return "Manhole cover";
    case 364: return "Lose 2 gold for useless advice";
    case 365: return "Meet servant";
    case 366: return "The mixture is awful";
    case 367: return "Lose most gold to get out";
    case 368: return "Vision";
    case 369: return "Back at junction";
    case 370: return "In the garden";
    case 371: return "Find healing mixture";
    case 372: return "Outside white house";
    case 373: return "Poison hurts";
    case 374: return "Get shield with unicorn crest";
    case 375: return "Wall with cheering behind it";
    case 376: return "Get magic helmet";
    case 377: return "See dark hole";
    case 379: return "Hurt and armour approaching";
    case 380: return "Soup is good";
    case 381: return "May buy advice";
    case 382: return "Ring of ice was useless";
    case 383: return "Corridor";
    case 384: return "Avoid and may chase dwarves";
    case 387: return "Copper brooch does nothing";
    case 388: return "Cannot get in";
    case 393: return "Escorted out of city";
    case 394: return "May talk to woman";
    case 395: return "Guilt from killing";
    case 396: return "Outside flower shop";
    case 397: return "Loot is 1 gold";
    case 398: return "May play cannonball game";
    case 399: return "Outside ship";
    case 400: return "Game won";
    case 401: return "Beaten Sourbelly";
    case 402: return "Throwing shield at Fatnose";
    case 403: return "Beaten Sourbelly";
    case 404: return "Draw sword";
    case 408: return "Big jump";
    case 411: return "Zanbar Bone kills you";
    case 412: return "The food is good";
    case 413: return "May listen to musician";
    case 417: return "May buy tattoo";
    case 423: return "Retrieved sword again";
    case 424: return "";
    case 425: return "No ring of fire";
    case 432: return "May see magic candle";
    case 433: return "Give second item to silversmith";
    case 434: return "Unconscious";
    case 435: return "";
    case 436: return "";
    case 437: return "";
    case 438: return "";
    case 439: return "";
    case 440: return "";
    case 441: return "";
    case 442: return "";
    case 443: return "";
    case 444: return "";
    case 445: return "";
    case 446: return "";
    case 447: return "";
    case 448: return "";
    case 449: return "";
    case 450: return "";
    default:
      std::cerr << "No description for chapter" << chapter_number;
      assert(!"Should not get here");
      return "";
  }
}

void Chapter::CharacterChanged(const Character& character) const
{
  assert(m_observer);
  m_observer->CharacterChanged(character);
}

void Chapter::Wait() const
{
  assert(m_observer);
  m_observer->Wait();
}

std::ostream& operator<<(std::ostream& os, const Chapter& chapter)
{
  os
    << "text: " << chapter.GetText() << '\n'
    << "# monsters: " << chapter.GetFighting().GetMonsters().size() << '\n'
  ;
  for (const auto& monster: chapter.GetFighting().GetMonsters())
  {
    os << monster << '\n';
  }
  os
    << "next_chapter: " << chapter.GetNextChapter() << '\n'
  ;
  return os;
}
