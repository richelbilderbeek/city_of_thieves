#ifndef PAWNSHOPCHAPTER_H
#define PAWNSHOPCHAPTER_H

#include <iosfwd>
#include <vector>

#include "item.h"

struct Chapter;
struct Character;

///Chapter where you can sell stuff
///State of Chapter
struct PawnShopChapter
{
  PawnShopChapter(Chapter * const chapter);
  PawnShopChapter(const PawnShopChapter&) = default;
  PawnShopChapter& operator=(const PawnShopChapter&) = default;

  void AddItem(const Item item, const int price);

  void Do(Character& character) const;

  const std::vector<std::pair<Item,int>>& GetItems() const noexcept { return m_items; }

  private:
  Chapter * m_chapter; //Will always point to its Chapter

  std::vector<std::pair<Item,int>> m_items;
};

PawnShopChapter ParsePawnShopChapter(std::stringstream& s, Chapter * const chapter);

#endif // PAWNSHOPCHAPTER_H
