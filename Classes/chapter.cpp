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
    case 155: return "";
    case 156: return "";
    case 157: return "";
    case 158: return "";
    case 159: return "";
    case 160: return "";
    case 161: return "";
    case 162: return "";
    case 163: return "";
    case 164: return "";
    case 165: return "";
    case 166: return "";
    case 167: return "";
    case 168: return "";
    case 169: return "";
    case 170: return "";
    case 171: return "";
    case 172: return "";
    case 173: return "";
    case 174: return "";
    case 175: return "";
    case 176: return "";
    case 177: return "";
    case 178: return "";
    case 179: return "";
    case 180: return "";
    case 181: return "";
    case 182: return "";
    case 183: return "";
    case 184: return "";
    case 185: return "";
    case 186: return "";
    case 187: return "";
    case 188: return "";
    case 189: return "";
    case 190: return "";
    case 191: return "";
    case 192: return "";
    case 193: return "";
    case 194: return "";
    case 195: return "";
    case 196: return "";
    case 197: return "";
    case 198: return "";
    case 199: return "";
    case 200: return "";
    case 201: return "";
    case 202: return "";
    case 203: return "";
    case 204: return "";
    case 205: return "Out of the sewers";
    case 206: return "";
    case 207: return "";
    case 208: return "";
    case 209: return "";
    case 211: return "";
    case 212: return "";
    case 213: return "";
    case 214: return "";
    case 215: return "";
    case 216: return "";
    case 217: return "";
    case 218: return "";
    case 219: return "";
    case 220: return "";
    case 221: return "";
    case 222: return "";
    case 223: return "";
    case 224: return "";
    case 225: return "";
    case 226: return "";
    case 227: return "";
    case 228: return "";
    case 229: return "";
    case 230: return "";
    case 231: return "";
    case 232: return "";
    case 233: return "";
    case 234: return "";
    case 235: return "";
    case 236: return "";
    case 237: return "";
    case 238: return "";
    case 239: return "";
    case 240: return "";
    case 241: return "";
    case 242: return "";
    case 243: return "";
    case 244: return "";
    case 245: return "";
    case 246: return "";
    case 247: return "";
    case 248: return "";
    case 249: return "";
    case 250: return "";
    case 251: return "";
    case 252: return "";
    case 253: return "";
    case 254: return "";
    case 255: return "";
    case 256: return "";
    case 257: return "";
    case 258: return "";
    case 259: return "";
    case 260: return "";
    case 261: return "";
    case 262: return "";
    case 263: return "";
    case 264: return "";
    case 265: return "";
    case 266: return "";
    case 267: return "";
    case 268: return "";
    case 269: return "";
    case 270: return "";
    case 271: return "";
    case 272: return "";
    case 273: return "";
    case 274: return "";
    case 275: return "";
    case 276: return "";
    case 277: return "";
    case 278: return "";
    case 279: return "";
    case 280: return "";
    case 281: return "";
    case 282: return "";
    case 283: return "";
    case 284: return "";
    case 285: return "";
    case 286: return "";
    case 287: return "";
    case 288: return "";
    case 289: return "";
    case 290: return "";
    case 291: return "";
    case 292: return "";
    case 293: return "";
    case 294: return "";
    case 295: return "";
    case 296: return "";
    case 297: return "";
    case 298: return "";
    case 299: return "";
    case 300: return "";
    case 301: return "";
    case 302: return "";
    case 303: return "";
    case 304: return "";
    case 305: return "Stalker is unaffected";
    case 306: return "";
    case 307: return "";
    case 308: return "";
    case 309: return "";
    case 310: return "Third floor";
    case 311: return "";
    case 312: return "";
    case 313: return "";
    case 314: return "";
    case 315: return "";
    case 316: return "";
    case 317: return "";
    case 318: return "";
    case 319: return "";
    case 320: return "";
    case 321: return "";
    case 322: return "";
    case 323: return "";
    case 324: return "";
    case 325: return "";
    case 326: return "";
    case 327: return "";
    case 328: return "";
    case 329: return "";
    case 330: return "";
    case 331: return "";
    case 332: return "";
    case 333: return "";
    case 334: return "";
    case 335: return "";
    case 336: return "";
    case 337: return "";
    case 338: return "";
    case 339: return "";
    case 340: return "";
    case 341: return "";
    case 342: return "";
    case 343: return "";
    case 344: return "";
    case 345: return "";
    case 346: return "";
    case 347: return "";
    case 348: return "";
    case 349: return "";
    case 350: return "";
    case 351: return "";
    case 352: return "";
    case 353: return "";
    case 354: return "";
    case 355: return "";
    case 356: return "";
    case 357: return "";
    case 358: return "";
    case 359: return "";
    case 360: return "";
    case 361: return "";
    case 362: return "";
    case 363: return "";
    case 364: return "";
    case 365: return "";
    case 366: return "";
    case 367: return "";
    case 368: return "";
    case 369: return "";
    case 370: return "";
    case 371: return "";
    case 372: return "";
    case 373: return "";
    case 374: return "";
    case 375: return "";
    case 376: return "";
    case 377: return "";
    case 378: return "";
    case 379: return "";
    case 380: return "";
    case 381: return "";
    case 382: return "";
    case 383: return "";
    case 384: return "";
    case 385: return "";
    case 386: return "";
    case 387: return "";
    case 388: return "";
    case 389: return "";
    case 390: return "";
    case 391: return "";
    case 392: return "";
    case 393: return "";
    case 394: return "";
    case 395: return "";
    case 396: return "";
    case 397: return "";
    case 398: return "";
    case 399: return "";
    case 400: return "Game won";
    case 401: return "";
    case 402: return "";
    case 403: return "";
    case 404: return "";
    case 405: return "";
    case 406: return "";
    case 407: return "";
    case 408: return "";
    case 409: return "";
    case 410: return "";
    case 411: return "";
    case 412: return "";
    case 413: return "";
    case 414: return "";
    case 415: return "";
    case 416: return "";
    case 417: return "";
    case 418: return "";
    case 419: return "";
    case 420: return "";
    case 421: return "";
    case 422: return "";
    case 423: return "";
    case 424: return "";
    case 425: return "";
    case 426: return "";
    case 427: return "";
    case 428: return "";
    case 429: return "";
    case 430: return "";
    case 431: return "";
    case 432: return "";
    case 433: return "";
    case 434: return "";
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
