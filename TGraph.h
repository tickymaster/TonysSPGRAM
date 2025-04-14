#ifndef TGRAPH_H
#define TGRAPH_H

#include <vector>
#include "CmplxNum.h"

class TGraph {
public:
	void displaySpectogram();
	std::vector<std::vector<int>> normalizeTo255(const std::vector<std::vector<double>>& dbMatrix);
};

#endif // TGRAPH_H