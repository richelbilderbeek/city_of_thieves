#ifndef ITEM_H
#define ITEM_H

#include <iosfwd>
#include <string>

enum class Item
{
  black_pearls = 1,
  carralifs_sword = 2, //Present at start, can lose it at 126
  chainmail_coat = 3,
  climbing_rope = 4,
  coloured_candle = 5, //Chapter 241
  copper_scorpion_brooch = 6, //Lose 1 luck without knowing
  cursed_white_silk_glove = 7,
  dexterity_potion = 8,
  eye_patch = 9,
  garlic = 10,
  glass_ball = 11,
  golden_owl = 12,
  golden_scorpion_brooch = 13, //Gives 2 luck, chapter 8
  gold_flower = 14,
  hags_hair = 15,
  invisibility_ring = 16,
  iron_key = 17,
  iron_spike = 18,
  ivory_skull_on_a_silver_chain = 19,
  knucklebones = 20, //NL: bikkels
  lantern = 21,
  lotus_flower = 22,
  luck_potion = 23,
  magic_elven_boots = 24,
  magic_helmet = 25, //Found in chapter 376. add 1 point to attack
  magnificent_shield = 26, //Found in chapter 340, raises attack strength by 1
  meat_hook = 27,
  merchant_pass = 28,
  mirror = 29,
  ordinary_sword = 30, //Obtain it at 126
  piece_of_chalk = 31,
  potion_of_mind_control = 32, //Obtained at 359
  ring_of_fire = 33,
  ring_of_ice = 34,
  ring_of_the_golden_eye = 35,
  set_of_keys = 36, //Obtained at 285
  shield = 37,
  shield_with_tower_crest = 38, //Found in chapter 125
  shield_with_unicorn_crest = 39, //Found in chapter 374
  silver_arrow = 40,
  silver_chalice = 41, //Chapter 220
  silver_flute = 42, //Obtained at 359
  silver_insect_bracelet = 43,
  silver_scorpion_brooch = 44, //Heals one condition after each battle
  silver_spoon = 45, //Chapter 220
  skeleton_key = 46,
  stale_brown_bread = 47,
  stale_white_bread = 48,
  stamina_potion = 49,
  tattoo = 50,
  throwing_knife = 51,
  two_gems = 52,
  two_silver_goblets = 53, //Chapter 220
  //Abstract items
  all_gold = 100, //For chapter 42
  all_provisions = 101, //For chapter 42
  all_silver_items = 102, //For chapter 343
  any_scorpion_brooch = 103,
  random_item_or_one_gold = 104, //For chapter 148
  two_random_items = 105, //For chapter 63, where you lose two random items
  //Below this, these are status changes
  all_needed_to_slay_zanbar_bone = 200,
  followed_sewer_north = 201, //Chapter 174
  followed_sewer_south = 202, //Chapter 118
  has_inspected_suit_of_armor = 203, //5th floor of Zanbar Bone's tower
  lifted_goblet_a = 204,
  lifted_goblet_b = 205, //Chapter 209
  lifted_goblet_c = 206,
  opened_pirate_captain_door = 207, //Chapter
  opened_pirate_crew_door   = 208, //Chapter 176
  picked_up_golden_scorpion = 209,
  picked_up_silver_scorpion = 210,
  seen_mummy = 211
};

std::string ToPrettyStr(const Item item);
std::string ToStr(const Item item);

Item ToItem(const std::string& item_name);
bool IsItem(const std::string& item_name);
bool IsSilver(const Item item);

//Is magic and non-cursed
bool IsMagic(const Item item);
std::ostream& operator<<(std::ostream& os, const Item item);

Item ReadItem(std::stringstream& s);

#endif // ITEM_H
