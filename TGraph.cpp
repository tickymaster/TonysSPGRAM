#include "iostream"
#include <vector>
#include "algorithm"
#include "cmath"
#include "TGraph.h"


void TGraph::displaySpectogram() {

}
std::vector<std::vector<int>> TGraph::normalizeTo255(const std::vector<std::vector<double>>& dbMatrix) {
    using namespace std;

    // Copy dimensions
    vector<vector<int>> matrix(dbMatrix.size(), vector<int>(dbMatrix[0].size()));

    // Find the minimum and maximum in the origninal data.
    double min_val = numeric_limits<double>::max();
    double max_val = numeric_limits<double>::lowest();
    for (auto& row : dbMatrix)
    {
        for (auto& value : row)
        {
            min_val = min(min_val, value);
            max_val = max(max_val, value);
        }
    }

    double range = max_val - min_val;
    if (range == 0) {
        range = 1;
    }

    // Normalize each element to the range [0, 255]
    for (size_t i = 0; i < dbMatrix.size(); i++)
    {
        for (size_t j = 0; j < dbMatrix[0].size(); j++)
        {
            double normalized = (dbMatrix[i][j] - min_val) / range * 255.0;
            matrix[i][j] = static_cast<int>(normalized);
        }
    }


    return matrix;
}

