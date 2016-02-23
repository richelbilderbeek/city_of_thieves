#include "shopchapter.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "chapter.h"
#include "character.h"
#include "helper.h"

ShopChapter::ShopChapter(Chapter * const chapter)
  : m_chapter{chapter}, m_items{}
{
}

void ShopChapter::AddItem(const Item item, const int price)
{
  m_items.push_back(std::make_pair(item,price));
}

void ShopChapter::Do(Character& character) const
{
  //Must be a copy, as the copy can get cleared
  std::vector<std::pair<Item,int>> items = this->GetItems();

  while (1)
  {
    if (items.empty())
    {
      m_chapter->ShowText("There are no more items to buy, so you leave the shop.\n");
      break;
    }
    std::vector<Option> options;
    options.push_back(CreateLeaveOption());

    for (const auto& item: items)
    {
      if (item.second > character.GetGold()) continue;
      if (character.HasItem(item.first)) continue;
      std::stringstream text;
      text
        << "Buy "
        << ToPrettyStr(item.first) << " for "
        << item.second << " gold pieces"
      ;
      Consequence consequence;
      consequence.AddItemToAdd(item.first);
      consequence.SetChangeGold(-item.second);
      Option option(text.str(),consequence);
      options.push_back(option);
    }

    //Shop
    const Option chosen{m_chapter->RequestOption(options)};
    if (chosen.GetConsequence().GetType() == ConsequenceType::leave) { break; }

    assert(!chosen.GetConsequence().GetItemsToAdd().empty());
    const Item item_bought{chosen.GetConsequence().GetItemsToAdd()[0]};

    m_chapter->ShowText("You bough " + ToPrettyStr(item_bought) + "\n");
    chosen.GetConsequence().Apply(character);
  }
}

ShopChapter ParseShopChapter(std::stringstream& s, Chapter * const chapter)
{
  const Helper h;
  ShopChapter c(chapter);
  while (1)
  {
    const std::string what{h.ReadString(s)};
    if (what == "@") break;
    assert(IsItem(what));
    const Item item{ToItem(what)};
    const int price{h.ReadInt(s)};
    c.AddItem(item,price);
  }
  return c;
}
