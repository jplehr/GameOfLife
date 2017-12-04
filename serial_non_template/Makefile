
PAPI_BASE_DIR=/opt/papi/install
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/all_repos/jplehr-c++PaPi -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/all_repos/jplehr-c++PaPi -lpapicpp -lpapi

CXXFLAGS=-I. -std=c++11 -Wall -pedantic

all: gol 

extra: gol.papi 

gol: main.cpp SerialGoL.cpp
	$(CXX) $(CXXFLAGS) -O3 SerialGoL.cpp main.cpp -o gol

gol-papi: main.cpp
	$(CXX) $(CXXFLAGS) -O2 $(PAPI_INC_FLAGS) main.cpp -o gol.papi $(PAPI_LD_FLAGS)

gol-clang: main.cpp SerialGoL.cpp
	clang++ -finstrument-functions -finstrument-functions-whitelist-inputfile=./filter.txt $(CXXFLAGS) -O3 SerialGoL.cpp main.cpp -o gol

gol-scorep: main.cpp SerialGoL.cpp
	scorep $(CXX) $(CXXFLAGS) -O3 SerialGoL.cpp -c
	scorep $(CXX) $(CXXFLAGS) -O3 main.cpp -c
	scorep $(CXX) $(CXXFLAGS) SerialGoL.o main.o -o gol.scorep


gol-scorep-filt: main.cpp SerialGoL.cpp
	scorep --instrument-filter=./scorep-filter-file $(CXX) $(CXXFLAGS) -O3 SerialGoL.cpp -c
	scorep --instrument-filter=./scorep-filter-file $(CXX) $(CXXFLAGS) -O3 main.cpp -c
	scorep --instrument-filter=./scorep-filter-file $(CXX) $(CXXFLAGS) SerialGoL.o main.o -o gol.scorep

gol-scorep-test: main.cpp SerialGoL.cpp
	scorep --instrument-filter=./instrumented-InclStatementCount50.txt $(CXX) $(CXXFLAGS) -O3 SerialGoL.cpp -c
	scorep --instrument-filter=./instrumented-InclStatementCount50.txt $(CXX) $(CXXFLAGS) -O3 main.cpp -c
	scorep --instrument-filter=./instrumented-InclStatementCount50.txt $(CXX) $(CXXFLAGS) SerialGoL.o main.o -o gol.scorep

clean:
	rm -f gol gol.templ gol.papi gol.omp gol.templ.omp gol.papi.finstr gol.scorep
