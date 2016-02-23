#include "item.h"

#include <algorithm>
#include <cassert>
#include <sstream>

#include "helper.h"

std::vector<std::pair<Item,std::string>> CreateItemBimap()
{
  using Pair = std::pair<Item,std::string>;
  static std::vector<Pair> m;
  {
    static bool is_done{false};
    if (is_done) return m;
    is_done = true;
  }
  m.push_back(Pair(Item::all_gold,"all_gold"));
  m.push_back(Pair(Item::all_needed_to_slay_zanbar_bone,"all_needed_to_slay_zanbar_bone"));
  m.push_back(Pair(Item::all_provisions,"all_provisions"));
  m.push_back(Pair(Item::all_silver_items,"all_silver_items"));
  m.push_back(Pair(Item::any_scorpion_brooch,"any_scorpion_brooch"));
  m.push_back(Pair(Item::black_pearls,"black_pearls"));
  m.push_back(Pair(Item::carralifs_sword,"carralifs_sword"));
  m.push_back(Pair(Item::chainmail_coat,"chainmail_coat"));
  m.push_back(Pair(Item::climbing_rope,"climbing_rope"));
  m.push_back(Pair(Item::coloured_candle,"coloured_candle"));
  m.push_back(Pair(Item::copper_scorpion_brooch,"copper_scorpion_brooch"));
  m.push_back(Pair(Item::cursed_white_silk_glove,"cursed_white_silk_glove"));
  m.push_back(Pair(Item::dexterity_potion,"dexterity_potion"));
  m.push_back(Pair(Item::eye_patch,"eye_patch"));
  m.push_back(Pair(Item::followed_sewer_north,"followed_sewer_north"));
  m.push_back(Pair(Item::followed_sewer_south,"followed_sewer_south"));
  m.push_back(Pair(Item::garlic,"garlic"));
  m.push_back(Pair(Item::glass_ball,"glass_ball"));
  m.push_back(Pair(Item::golden_owl,"golden_owl"));
  m.push_back(Pair(Item::golden_scorpion_brooch,"golden_scorpion_brooch"));
  m.push_back(Pair(Item::gold_flower,"gold_flower"));
  m.push_back(Pair(Item::hags_hair,"hags_hair"));
  m.push_back(Pair(Item::has_inspected_suit_of_armor,"has_inspected_suit_of_armor"));
  m.push_back(Pair(Item::invisibility_ring,"invisibility_ring"));
  m.push_back(Pair(Item::iron_key,"iron_key"));
  m.push_back(Pair(Item::iron_spike,"iron_spike"));
  m.push_back(Pair(Item::ivory_skull_on_a_silver_chain,"ivory_skull_on_a_silver_chain"));
  m.push_back(Pair(Item::seen_mummy,"seen_mummy"));
  m.push_back(Pair(Item::knucklebones,"knucklebones"));
  m.push_back(Pair(Item::lantern,"lantern"));
  m.push_back(Pair(Item::lifted_goblet_a,"lifted_goblet_a"));
  m.push_back(Pair(Item::lifted_goblet_b,"lifted_goblet_b"));
  m.push_back(Pair(Item::lifted_goblet_c,"lifted_goblet_c"));
  m.push_back(Pair(Item::lotus_flower,"lotus_flower"));
  m.push_back(Pair(Item::luck_potion,"luck_potion"));
  m.push_back(Pair(Item::magic_elven_boots,"magic_elven_boots"));
  m.push_back(Pair(Item::magic_helmet,"magic_helmet"));
  m.push_back(Pair(Item::magnificent_shield,"magnificent_shield"));
  m.push_back(Pair(Item::meat_hook,"meat_hook"));
  m.push_back(Pair(Item::merchant_pass,"merchant_pass"));
  m.push_back(Pair(Item::mirror,"mirror"));
  m.push_back(Pair(Item::opened_pirate_captain_door,"opened_pirate_captain_door"));
  m.push_back(Pair(Item::opened_pirate_crew_door,"opened_pirate_crew_door"));
  m.push_back(Pair(Item::ordinary_sword,"ordinary_sword"));
  m.push_back(Pair(Item::picked_up_golden_scorpion,"picked_up_golden_scorpion"));
  m.push_back(Pair(Item::picked_up_silver_scorpion,"picked_up_silver_scorpion"));
  m.push_back(Pair(Item::piece_of_chalk,"piece_of_chalk"));
  m.push_back(Pair(Item::potion_of_mind_control,"potion_of_mind_control"));
  m.push_back(Pair(Item::random_item_or_one_gold,"random_item_or_one_gold"));
  m.push_back(Pair(Item::ring_of_fire,"ring_of_fire"));
  m.push_back(Pair(Item::ring_of_ice,"ring_of_ice"));
  m.push_back(Pair(Item::ring_of_the_golden_eye,"ring_of_the_golden_eye"));
  m.push_back(Pair(Item::set_of_keys,"set_of_keys"));
  m.push_back(Pair(Item::shield,"shield"));
  m.push_back(Pair(Item::shield_with_tower_crest,"shield_with_tower_crest"));
  m.push_back(Pair(Item::shield_with_unicorn_crest,"shield_with_unicorn_crest"));
  m.push_back(Pair(Item::silver_arrow,"silver_arrow"));
  m.push_back(Pair(Item::silver_chalice,"silver_chalice"));
  m.push_back(Pair(Item::silver_flute,"silver_flute"));
  m.push_back(Pair(Item::silver_insect_bracelet,"silver_insect_bracelet"));
  m.push_back(Pair(Item::silver_scorpion_brooch,"silver_scorpion_brooch"));
  m.push_back(Pair(Item::silver_spoon,"silver_spoon"));
  m.push_back(Pair(Item::skeleton_key,"skeleton_key"));
  m.push_back(Pair(Item::stale_brown_bread,"stale_brown_bread"));
  m.push_back(Pair(Item::stale_white_bread,"stale_white_bread"));
  m.push_back(Pair(Item::stamina_potion,"stamina_potion"));
  m.push_back(Pair(Item::tattoo,"tattoo"));
  m.push_back(Pair(Item::throwing_knife,"throwing_knife"));
  m.push_back(Pair(Item::two_gems,"two_gems"));
  m.push_back(Pair(Item::two_random_items,"two_random_items"));
  m.push_back(Pair(Item::two_silver_goblets,"two_silver_goblets"));
  return m;
}

bool IsItem(const std::string& item_name)
{
  using Pair = std::pair<Item,std::string>;
  const auto m = CreateItemBimap();
  return std::find_if(
    std::begin(m),
    std::end(m),
    [item_name](const Pair& p) { return p.second == item_name; }
  ) != std::end(m);
}

bool IsMagic(const Item item)
{
  return
       item == Item::magic_elven_boots
    || item == Item::magic_helmet
    || item == Item::silver_scorpion_brooch
    || item == Item::golden_scorpion_brooch
    || item == Item::copper_scorpion_brooch
    || item == Item::invisibility_ring
    || item == Item::ring_of_fire
    || item == Item::ring_of_ice
    || item == Item::ring_of_the_golden_eye
    || item == Item::silver_insect_bracelet
  ;
}

bool IsSilver(const Item item)
{
  return
       item == Item::ivory_skull_on_a_silver_chain
    || item == Item::silver_arrow
    || item == Item::silver_chalice
    || item == Item::silver_flute
    || item == Item::silver_insect_bracelet
    || item == Item::silver_scorpion_brooch
    || item == Item::silver_spoon
    || item == Item::two_silver_goblets
  ;
}

Item ReadItem(std::stringstream& s)
{
  int number = -1;
  s >> number;
  assert(number > -1);
  const Item item = static_cast<Item>(number);
  return item;
}

Item ToItem(const std::string& item_name)
{

  assert(IsItem(item_name));

  using Pair = std::pair<Item,std::string>;
  const auto m = CreateItemBimap();
  return std::find_if(
    std::begin(m),
    std::end(m),
    [item_name](const Pair& p) { return p.second == item_name; }
  )->first;
}

std::string ToPrettyStr(const Item item)
{
  return Helper().ToPretty(ToStr(item));
}

std::string ToStr(const Item item)
{
  using Pair = std::pair<Item,std::string>;
  const auto m = CreateItemBimap();
  const auto iter = std::find_if(
    std::begin(m),
    std::end(m),
    [item](const Pair& p) { return p.first == item; }
  );
  assert(iter != std::end(m));
  return iter->second;
}

std::ostream& operator<<(std::ostream& os, const Item item)
{
  os << ToStr(item);
  return os;
}
