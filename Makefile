
PAPI_BASE_DIR=/shared/apps/papi/5.4.0
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/all_repos/jplehr-c++PaPi -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/all_repos/jplehr-c++PaPi -lpapicpp -lpapi

all: gof gof-papi

gof: main.cpp
	$(CXX) -std=c++11 main.cpp -o gof

gof-papi: main.cpp
	$(CXX) -std=c++11 $(PAPI_INC_FLAGS) main.cpp -o gof-papi $(PAPI_LD_FLAGS)
