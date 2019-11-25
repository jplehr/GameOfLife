#include "SerialGoL.h"

#include <iostream>
#include <string>

int main(int argc, char **argv){

  int size = 50;
  if (argc == 2) {
    size = std::stoi(argv[1]);
  }
#ifdef PAPI_MEASUREMENT
	PapiW_start();
#endif

	GameOfLife gof(size, size);
	gof.init();
	for(int i = 0; i < 100; ++i){
		gof.tick();
	}

#ifdef PAPI_MEASUREMENT
	PapiW_stopAndPrint();
#endif

	std::cout << "Ended running GOL" << std::endl;

	return 0;
}
