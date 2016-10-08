#include "dice.h"

#include <cassert>

Dice * Dice::m_instance = nullptr;

Dice::Dice()
  : m_distribution(1,6),
    m_engine{}
{

}

Dice * Dice::Get()
{
  if (!m_instance) { m_instance = new Dice;}
  return m_instance;
}

void Dice::SetSeed(const int seed)
{
  m_engine = std::mt19937(seed);
  m_distribution = std::uniform_int_distribution<int>(1,6);
}


int Dice::Throw() noexcept
{
  const int dice_throw{
    m_distribution(m_engine)
  };
  assert(dice_throw >= 1 && dice_throw <= 6);
  return dice_throw;
}
