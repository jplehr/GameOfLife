#include "SerialTemplateGoL.h"

struct InitFunc {
	public:
		double operator()(int i, int j){
			return (double(i)*i - i*j/(i+j+1.0));
		}
};


int main(int argc, char **argv){

	GameOfLife<char, GoLStencil<char>> gol(1000, 1000);
	MyInit f;
	gol.init(f);

//	gol.print(std::cout);

	for(int i = 0; i < 100; ++i){
		gol.tick();
	}

//	gol.print(std::cout);

	return 0;
}
