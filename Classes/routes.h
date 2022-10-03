#ifndef ROUTES_H
#define ROUTES_H

/// Collect all routes in the game
class Routes
{
public:
  Routes(
    const int startingChapter = 0,
    const int finalChapter = 400
  );

  auto GetFinalChapter() const noexcept { return mFinalChapter; }
  auto GetStartingChapter() const noexcept { return mStartingChapter; }

private:

  int mStartingChapter;
  int mFinalChapter;
};

#endif // ROUTES_H
