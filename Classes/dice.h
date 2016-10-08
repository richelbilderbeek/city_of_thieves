#ifndef DICE_H
#define DICE_H

#include <random>

///A Singleton
struct Dice
{
  using Engine = std::mt19937;

  static Dice * Get();

  Engine& GetEngine() noexcept { return m_engine; }
  void SetSeed(const int seed);
  int Throw() noexcept;

  private:
  Dice();
  static Dice * m_instance;

  std::uniform_int_distribution<int> m_distribution;
  Engine m_engine;
};

#endif // DICE_H
