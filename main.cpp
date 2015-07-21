#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

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
class GameOfLife {

	public:
		GameOfLife(int numX, int numY) : dimX(numX), dimY(numY), grid(dimX*dimY){}

		void init();
		void print(std::ostream &out);

		void tick();

	private:
		void applyRules(int i, int j, std::vector<char> &newGrid);
		int getNumLiveNeighbors(int i, int j);
		int getIdx(int i, int j);

		int dimX, dimY;
		std::vector<char> grid;
};

void GameOfLife::tick(){
	std::vector<char> newGrid(dimX * dimY);
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			applyRules(i, j, newGrid);
		}
	}

	std::swap(grid, newGrid);
}

void GameOfLife::init(){
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

void GameOfLife::print(std::ostream &out){
	for(int i = 0; i < dimX; ++i){
		for(int j = 0; j < dimY; ++j){
			out << (grid.at(getIdx(i, j)) == 'l'? "1 " : "0 ");
		}
		out << "\n";
	}
	out << std::endl;
}

void GameOfLife::applyRules(int i, int j, std::vector<char> &newGrid){
	int numLiveNeighbors = getNumLiveNeighbors(i, j);

	int idx = getIdx(i, j);
	bool caseVisited;

	if(grid.at(idx) == 'l' && numLiveNeighbors < 2){
		newGrid.at(idx) = 'd';
		caseVisited = true;
	}

	if(grid.at(idx) == 'l'){
		if(numLiveNeighbors == 2 || numLiveNeighbors == 3){
			newGrid.at(idx) = 'l';
			caseVisited = true;
		}
	}

	if(grid.at(idx) == 'l' && numLiveNeighbors > 3){
		newGrid.at(idx) = 'd';
		caseVisited = true;
	}

	if(grid.at(idx) == 'd' && numLiveNeighbors == 3){
		newGrid.at(idx) = 'l';
		caseVisited = true;
	}

	if(!caseVisited){
		newGrid.at(idx) = grid.at(idx);
		caseVisited = true;
	}

	assert(caseVisited && "I assume that all grid points are processed with one of the cases.");
}

int GameOfLife::getIdx(int i, int j){
	return j * dimX + i;
}

int GameOfLife::getNumLiveNeighbors(int i, int j){
	int neighbors = 0;
	int idx = getIdx(i, j);

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



int main(int argc, char **argv){

	GameOfLife gof(100, 100);
	gof.init();
	gof.print(std::cout);
	for(int i = 0; i < 100; ++i){
		gof.tick();
	}
	gof.print(std::cout);

	return 0;
}
