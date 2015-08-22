#include "SerialTemplateGoL.h"

struct InitFunc {
	public:
		double operator()(int i, int j){
			return (double(i)*i - i*j/(i+j+1.0));
		}
};


int main(int argc, char **argv){

	GameOfLife<double> gol(10, 10);
	InitFunc f;
	gol.init(f);

	gol.print(std::cout);

	for(int i = 0; i != 10; ++i){
		gol.tick();
	}

	gol.print(std::cout);

	return 0;
}
