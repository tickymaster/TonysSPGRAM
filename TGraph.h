#ifndef TGRAPH_H
#define TGRAPH_H

#include <vector>
#include "CmplxNum.h"

class TGraph {
public:
	void displaySpectogram();
	std::vector<std::vector<int16_t>> normaliseData(std::vector<std::vector<int16_t>>& MagnitudesMatrix);
};

#endif // TGRAPH_H