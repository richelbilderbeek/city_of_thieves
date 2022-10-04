#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
/// Get the classical winning chapter sequence
/// Returns a vector with 'v[i] = j',
/// which indicates that at chapter i, go to chapter v[i]
std::vector<int> GetWinningRoute() noexcept;

#endif // ROUTE_H
