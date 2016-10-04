#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <omp.h>

#ifdef PAPI_MEASUREMENT
	#include "PapiInstance.h"
#endif

struct InitFunction {
	int operator()(int i, int j){
		const int v = (j-i > 0)?j-i:1;
		int r = (i+j) / (1 + v);
		return (r == 0) ? i+1 : r;
	}
};

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

void OpenMPGameOfLife::tick(){
	std::vector<char> newGrid(dimX * dimY);

	#pragma omp parallel for shared(newGrid)
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			applyRules(i, j, newGrid);
		}
	}

	std::swap(grid, newGrid);
}

void OpenMPGameOfLife::init(){
	InitFunction func;
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			int idx = getIdx(i, j);
			if(idx % func(i, j) == 0){
				grid.at(idx) = 'l';
			} else {
				grid.at(idx) = 'd';
			}
		}
	}
}

void OpenMPGameOfLife::print(std::ostream &out){
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			out << (grid.at(getIdx(i, j)) == 'l'? "1 " : "0 ");
		}
		out << "\n";
	}
	out << std::endl;
}

void OpenMPGameOfLife::applyRules(int i, int j, std::vector<char> &newGrid){
	int numLiveNeighbors = getNumLiveNeighbors(i, j);

	int idx = getIdx(i, j);

	if(grid.at(idx) == 'l' && numLiveNeighbors < 2){
		newGrid.at(idx) = 'd';
		return;
	}

	if(grid.at(idx) == 'l'){
		if(numLiveNeighbors == 2 || numLiveNeighbors == 3){
			newGrid.at(idx) = 'l';
			return;
		}
	}

	if(grid.at(idx) == 'l' && numLiveNeighbors > 3){
		newGrid.at(idx) = 'd';
		return;
	}

	if(grid.at(idx) == 'd' && numLiveNeighbors == 3){
		newGrid.at(idx) = 'l';
		return;
	}

	newGrid.at(idx) = grid.at(idx);
}

const int OpenMPGameOfLife::getIdx(int i, int j) const {
	return j * dimX + i;
}

const int OpenMPGameOfLife::getNumLiveNeighbors(int i, int j) const {
	int neighbors = 0;

	int n = getIdx(i-1, j);
	int ne = getIdx(i-1, j+1);
	int e = getIdx(i, j+1);
	int se = getIdx(i+1, j+1);
	int s = getIdx(i+1, j);
	int sw = getIdx(i+1, j-1);
	int w = getIdx(i, j-1);
	int nw = getIdx(i-1, j-1);

	auto neighborElems = {n, ne, e, se, s , sw, w, nw};
	for(const auto &neighbor : neighborElems){
		if(neighbor >= 0 && neighbor < grid.size()){
			if(grid.at(neighbor) == 'l'){
				neighbors++;
			}
		}
	}

	return neighbors;
}


