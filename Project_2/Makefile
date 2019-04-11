CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 
USERID=Group6
CLASSES=

all: my-router Network 

my-router: $(CLASSES)
	$(CXX)  $(CXXFLAGS) $@.cpp router.cpp msg.cpp -o $@ $^

Netwotk: $(CLASSES)
	$(CXX)  $(CXXFLAGS) $@.cpp Network.cpp router.cpp -o $@ $^


clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM my-router Network *.tar.gz

tarball: clean
	tar -cvf $(USERID).tar.gz *
