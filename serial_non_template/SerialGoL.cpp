#include "SerialGoL.h"


struct InitFunction {
	int operator()(int i, int j){
		const int v = (j-i > 0)?j-i:1;
		int r = (i+j) / (1 + v);
		return (r == 0) ? i+1 : r;
	}
};

void GameOfLife::tick(){
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			applyRules(i, j, gridB);
		}
	}

	std::swap(gridA, gridB);
}

void GameOfLife::init(){
	InitFunction func;
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			int idx = getIdx(i, j);
			if(idx % func(i, j) == 0){
				gridA.at(idx) = 'l';
			} else {
				gridA.at(idx) = 'd';
			}
		}
	}
}

void GameOfLife::print(std::ostream &out){
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			out << (gridA.at(getIdx(i, j)) == 'l'? "1 " : "0 ");
		}
		out << "\n";
	}
	out << std::endl;
}

void GameOfLife::applyRules(int i, int j, std::vector<char> &newGrid){
	int numLiveNeighbors = getNumLiveNeighbors(i, j);

	int idx = getIdx(i, j);

	if(gridA.at(idx) == 'l' && numLiveNeighbors < 2){
		newGrid.at(idx) = 'd';
		return;
	}

	if(gridA.at(idx) == 'l'){
		if(numLiveNeighbors == 2 || numLiveNeighbors == 3){
			newGrid.at(idx) = 'l';
			return;
		}
	}

	if(gridA.at(idx) == 'l' && numLiveNeighbors > 3){
		newGrid.at(idx) = 'd';
		return;
	}

	if(gridA.at(idx) == 'd' && numLiveNeighbors == 3){
		newGrid.at(idx) = 'l';
		return;
	}

	newGrid.at(idx) = gridA.at(idx);
}

const int GameOfLife::getIdx(int i, int j) const {
	return j * dimX + i;
}

const int GameOfLife::getNumLiveNeighbors(int i, int j) const {
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
		if(neighbor >= 0 && neighbor < gridA.size()){
			if(gridA.at(neighbor) == 'l'){
				neighbors++;
			}
		}
	}

	return neighbors;
}

