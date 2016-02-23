#ifndef CONSEQUENCETYPE_H
#define CONSEQUENCETYPE_H

enum class ConsequenceType
{
  normal,
  show_inventory,
  yes,
  no,
  leave, //Leave shop or pawn_shop
  eat_provision,
  drink_potion
};

#endif // CONSEQUENCETYPE_H
