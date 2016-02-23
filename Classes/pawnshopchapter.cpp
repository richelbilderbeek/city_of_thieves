#include "pawnshopchapter.h"

#include <cassert>
#include <sstream>

#include "chapter.h"
#include "character.h"
#include "helper.h"

PawnShopChapter::PawnShopChapter(Chapter * const chapter)
  : m_chapter{chapter}, m_items{}
{

}

void PawnShopChapter::AddItem(const Item item, const int price)
{
  m_items.push_back(std::make_pair(item,price));
}

void PawnShopChapter::Do(Character& character) const
{
  //Must be a copy, as the copy can get cleared
  std::vector<std::pair<Item,int>> items = this->GetItems();

  while (1)
  {
    std::vector<Option> options;
    options.push_back(CreateLeaveOption());

    for (const auto& item: items)
    {
      if (!character.HasItem(item.first)) continue;
      std::stringstream text;
      text
        << "Sell "
        << ToPrettyStr(item.first) << " for "
        << item.second << " gold pieces"
      ;
      Consequence consequence;
      consequence.AddItemToRemove(item.first);
      consequence.SetChangeGold(item.second);
      Option option(text.str(),consequence);
      options.push_back(option);
    }
    //Pawn shop
    const Option chosen{m_chapter->RequestOption(options)};
    if (chosen.GetConsequence().GetType() == ConsequenceType::leave) { break; }

    assert(!chosen.GetConsequence().GetItemsToRemove().empty());
    const Item item_sold{chosen.GetConsequence().GetItemsToRemove()[0]};

    m_chapter->ShowText("You sold " + ToPrettyStr(item_sold) + "\n");
    chosen.GetConsequence().Apply(character);
  }
}

PawnShopChapter ParsePawnShopChapter(std::stringstream& s, Chapter * const chapter)
{
  const Helper h;
  PawnShopChapter c(chapter);
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
