
PAPI_BASE_DIR=/opt/papi/install
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/all_repos/jplehr-c++PaPi -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/all_repos/jplehr-c++PaPi -lpapicpp -lpapi

CXXFLAGS=-I. -std=c++11 -Wall -pedantic

all: gol-templ 

extra: gol-papi 

gol-templ: main.cpp
	$(CXX) $(CXXFLAGS) -fopenmp -O3 main.cpp -o gol-templ

gol-papi: main.cpp
	$(CXX) $(CXXFLAGS) -O2 $(PAPI_INC_FLAGS) main.cpp -o gol-papi $(PAPI_LD_FLAGS)


clean:
	rm -f gol gol-templ gol-papi gol-omp gol-templ-omp gol-papi-finstr
