#ifndef SEARCH_NEAREST_H
#define SEARCH_NEAREST_H

#include <vector>
#include <cmath>
#include <limits>

using namespace std;

/**
 * @brief Clase para encontrar la ubicación más cercana.
 */
class SearchNearest {
public:
    /**
     * @brief Busca la central más cercana.
     */
    static pair<int, int> Find(const vector<pair<int, int>>& centrals, const pair<int, int>& new_contract) {
        int index = -1;
        double minDist = numeric_limits<double>::max();

        for (size_t i = 0; i < centrals.size(); i++) {
            double dx = centrals[i].first - new_contract.first;
            double dy = centrals[i].second - new_contract.second;
            double dist = sqrt(dx * dx + dy * dy);

            if (dist < minDist) {
                minDist = dist;
                index = i;
            }
        }

        return (index != -1) ? centrals[index] : make_pair(0, 0);
    }
};

#endif
