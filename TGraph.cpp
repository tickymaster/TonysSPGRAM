#include "iostream"
#include <vector>
#include "algorithm"
#include "cmath"
#include "TGraph.h"


void TGraph::displaySpectogram() {

}
std::vector<std::vector<int16_t>> TGraph::normaliseData(std::vector<std::vector<int16_t>>& MagnitudesMatrix) {
	using namespace std;

	int16_t max_val = numeric_limits<int16_t>::lowest();
	int16_t min_val = numeric_limits<int16_t>::max();

	for (const auto& row : MagnitudesMatrix)
	{
		for (int16_t val : row)
		{
			min_val = min(min_val, val);
			max_val = max(max_val, val);
		}
	}

	if (max_val == min_val) {
		cerr << "All values in matrix are the same, normalization is ambiguous." << endl;
		return vector<vector<int16_t>>(MagnitudesMatrix.size(), vector<int16_t>(MagnitudesMatrix[0].size(), 0));
	}

	vector<vector<int16_t>> normalised(MagnitudesMatrix.size(), vector<int16_t>(MagnitudesMatrix[0].size(), 0));

	for (size_t i = 0; i < MagnitudesMatrix.size(); i++)
	{
		for (size_t j = 0; j < MagnitudesMatrix[i].size(); j++)
		{
			normalised[i][j] = static_cast<int16_t>(
				255.0 * (MagnitudesMatrix[i][j] - min_val) / static_cast<double>(max_val - min_val)
				);
		}
	}
		
	return normalised;
}	
