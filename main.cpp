#include "SerialGoL.h"

int main(int argc, char **argv){
#ifdef PAPI_MEASUREMENT
	PapiW_start();
#endif

	GameOfLife gof(150,150);
	gof.init();
	for(int i = 0; i < 100; ++i){
		gof.tick();
	}

#ifdef PAPI_MEASUREMENT
	PapiW_stopAndPrint();
#endif

	return 0;
}
