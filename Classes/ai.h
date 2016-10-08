#ifndef AI_H
#define AI_H

#include <iosfwd>
#include <random>
#include <set>
#include <map>
#include "option.h"
#include "game.h"
#include "observer.h"

///The articial intelligence
struct Ai final : public Observer
{
  using Key = std::string;
  using Keys = std::vector<Key>;
  using Payoff = double;
  using PayoffPair = std::pair<Key,Payoff>;
  using PayoffPairs = std::vector<PayoffPair>;

  Ai();
  Ai(const Ai& ai) = delete;
  Ai& operator=(const Ai& ai) = delete;

  Payoff CalcFinalPayoff(const Character& character) const noexcept;

  ///Create a graph that shows the payoffs
  void CreateGraph() const noexcept;

  //Chapter of current sequence
  const Keys& GetChapters() const noexcept { return m_keys; }


  //Payoff for each chapter
  const PayoffPairs& GetPayoffs() const noexcept { return m_payoffs; }

  int GetNumberOfCharsPerLine() const noexcept override { return 80; }

  double GetPayoff(const std::string& option_text) const noexcept;

  void SetPayoff(const Key& chapter, const Payoff& payoff);

  void SetFinalPayoff(const Payoff& final_payoff);

  void Start();

  private:

  std::uniform_real_distribution<double> m_distribution;
  std::mt19937 m_engine;

  Game * m_game;

  ///All the keys (option texts) that were chosen
  Keys m_keys;

  //Payoff for each key
  mutable PayoffPairs m_payoffs;

  bool m_silent;

  mutable std::map<Item,double> m_tally;

  void CharacterChanged(const Character&) override {} //Ignore
  Option RequestOption(const std::vector<Option>& options) override;
  void ShowText(const std::string& text) override;
  void Wait() override;

};

void SolveGame();

std::ostream& operator<<(std::ostream& os, const Ai& ai);

#endif // AI_H
