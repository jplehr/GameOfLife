#include "SerialGoL.h"

int main(int argc, char **argv){
#ifdef PAPI_MEASUREMENT
	Papi papi;
	PapiInstance *instance = papi.create();
	instance->addEvent(PAPI_TOT_INS);
	instance->addEvent(PAPI_BR_MSP);
	instance->start();
#endif

	GameOfLife gof(1000, 1000);
	gof.init();
//	gof.print(std::cout);
	for(int i = 0; i < 100; ++i){
		gof.tick();
	}
//	gof.print(std::cout);

#ifdef PAPI_MEASUREMENT
	instance->stop();
	std::cout << "\nThe measured total instructions were: " << instance->getEventValue(PAPI_TOT_INS) << "\n";
	std::cout << "The measured mispredicted branches were: " << instance->getEventValue(PAPI_BR_MSP) << std::endl;
#endif

	return 0;
}
