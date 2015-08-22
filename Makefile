
PAPI_BASE_DIR=/shared/apps/papi/5.4.0
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/all_repos/jplehr-c++PaPi -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/all_repos/jplehr-c++PaPi -lpapicpp -lpapi

CXXFLAGS=-I. -std=c++11

all: gol gol-templ gol-papi gol-omp gol-templ-omp

gol: main.cpp
	$(CXX) $(CXXFLAGS) -O3 main.cpp -o gol
gol-omp: ompMain.cpp
	$(CXX) $(CXXFLAGS) -O3 -fopenmp ompMain.cpp -o gol-omp



gol-templ: TemplateMain.cpp
	$(CXX) $(CXXFLAGS) -O3 TemplateMain.cpp -o gol-templ

gol-templ-omp: ompTemplateMain.cpp
	$(CXX) $(CXXFLAGS) -O3 -fopenmp ompTemplateMain.cpp -o gol-templ-omp



gol-papi: main.cpp
	$(CXX) -std=c++11 $(PAPI_INC_FLAGS) main.cpp -o gol-papi $(PAPI_LD_FLAGS)



clean:
	rm -f gol gol-templ gol-papi gol-omp gol-templ-omp
