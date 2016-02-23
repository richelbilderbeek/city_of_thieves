#ifndef SHOPCHAPTER_H
#define SHOPCHAPTER_H

#include <iosfwd>
#include <vector>

#include "item.h"

struct Chapter;
struct Character;

///Chapter where you can buy stuff
struct ShopChapter
{
  ShopChapter(Chapter * const chapter);
  ShopChapter(const ShopChapter&) = default;
  ShopChapter& operator=(const ShopChapter&) = default;

  void AddItem(const Item item, const int price);

  void Do(Character& character) const;

  const std::vector<std::pair<Item,int>>& GetItems() const noexcept { return m_items; }

  private:
  Chapter * m_chapter; //Will always point to its Chapter

  std::vector<std::pair<Item,int>> m_items;
};

ShopChapter ParseShopChapter(std::stringstream& s, Chapter * const chapter);

#endif // SHOPCHAPTER_H
