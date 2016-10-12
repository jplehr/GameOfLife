#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

#ifdef PAPI_MEASUREMENT
//	#include "PapiInstance.h"

extern "C" {

	void PapiW_start() __attribute__((no_instrument_function));
	void PapiW_stopAndPrint() __attribute__((no_instrument_function));

}



#endif
/**
 * Some playground stuff.
 * Maybe usefull for some measurements?
 */
class GameOfLife {

	public:
		GameOfLife(int numX, int numY) : dimX(numX), dimY(numY), gridA(dimX*dimY), gridB(dimX*dimY){}

		void init();
		void print(std::ostream &out);

		void tick();

	private:
		void applyRules(int i, int j, std::vector<char> &newGrid);
		const int getNumLiveNeighbors(int i, int j) const;
		const int getIdx(int i, int j) const;

		const int dimX, dimY;
		std::vector<char> gridA, gridB;
};

