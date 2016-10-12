#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <omp.h>

#ifdef PAPI_MEASUREMENT
	#include "PapiInstance.h"
#endif

/**
 * Some playground stuff.
 * Maybe usefull for some measurements?
 */
class OpenMPGameOfLife {

	public:
		OpenMPGameOfLife(int numX, int numY) : dimX(numX), dimY(numY), grid(dimX*dimY){}

		void init();
		void print(std::ostream &out);

		void tick();

	private:
		void applyRules(int i, int j, std::vector<char> &newGrid);
		const int getNumLiveNeighbors(int i, int j) const;
		const int getIdx(int i, int j) const;

		const int dimX, dimY;
		std::vector<char> grid;
};

