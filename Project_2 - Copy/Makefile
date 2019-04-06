CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 
USERID=EDIT_MAKE_FILE
CLASSES=

all: main

my-router: $(CLASSES)
	$(CXX)  $(CXXFLAGS) $@.cpp NetworkGraph.cpp -o $@ $^

