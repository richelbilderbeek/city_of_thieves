#ifndef ROUTE_H
#define ROUTE_H

#include <vector>

/// Get the classical winning chapter sequence
/// Returns a vector with 'v[i] = j',
/// which indicates that at chapter i, go to chapter v[i]
std::vector<int> GetWinningRoute() noexcept;

/// Collect all routes that make sense
std::vector<std::vector<int>> GetSaneRoutes() noexcept;



#endif // ROUTE_H
