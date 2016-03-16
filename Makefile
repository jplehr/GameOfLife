
PAPI_BASE_DIR=/opt/papi/install
PAPI_INC_DIR=$(PAPI_BASE_DIR)/include
PAPI_LIB_DIR=$(PAPI_BASE_DIR)/lib

PAPI_INC_FLAGS=-I$(PAPI_INC_DIR) -I$(HOME)/Documents/all_repos/jplehr-PapiWrapper -DPAPI_MEASUREMENT
PAPI_LD_FLAGS=-L$(PAPI_LIB_DIR) -L$(HOME)/Documents/all_repos/jplehr-PapiWrapper -lpapicpp -lpapi

CXXFLAGS=-I. -std=c++11 -Wall -pedantic

all: gol gol-templ gol-omp gol-templ-omp

extra: gol-papi 

gol: main.cpp
	$(CXX) $(CXXFLAGS) -O3 main.cpp -o gol
gol-omp: ompMain.cpp
	$(CXX) $(CXXFLAGS) -O3 -fopenmp ompMain.cpp -o gol-omp
gol-finstr: main.cpp
	$(CXX) $(CXXFLAGS) -finstrument-functions -O3 main.cpp -o gol-finstr


gol-templ: TemplateMain.cpp
	$(CXX) $(CXXFLAGS) -O3 TemplateMain.cpp -o gol-templ

gol-templ-omp: ompTemplateMain.cpp
	$(CXX) $(CXXFLAGS) -finstrument-functions -O3 -fopenmp ompTemplateMain.cpp -o gol-templ-omp



gol-papi: main.cpp
	$(CXX) $(CXXFLAGS) $(PAPI_INC_FLAGS) main.cpp -o gol-papi $(PAPI_LD_FLAGS)

gol-papi-finstr: main.cpp
	$(CXX) $(CXXFLAGS) -finstrument-functions $(PAPI_INC_FLAGS) main.cpp -o gol-papi-finstr $(PAPI_LD_FLAGS) -lem


clean:
	rm -f gol gol-templ gol-papi gol-omp gol-templ-omp gol-papi-finstr
