
PAPI_BASE_DIR=/opt/papi/install
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/all_repos/jplehr-c++PaPi -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/all_repos/jplehr-c++PaPi -lpapicpp -lpapi

CXXFLAGS=-I. -std=c++11 -Wall -pedantic

all: gol-omp

extra: gol-papi 

gol-omp: main.cpp OpenMPGoL.cpp
	$(CXX) $(CXXFLAGS) -O3 -fopenmp OpenMPGoL.cpp main.cpp -o gol-omp


gol-papi: main.cpp
	$(CXX) $(CXXFLAGS) -O2 $(PAPI_INC_FLAGS) main.cpp -o gol-papi $(PAPI_LD_FLAGS)

clean:
	rm -f gol-omp
