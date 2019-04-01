CXX=g++
CXXOPTIMIZE= -O2
CXXFLAGS= -g -Wall -pthread -std=c++11 
USERID=EDIT_MAKE_FILE
CLASSES=

all: my-router 

my-router: $(CLASSES)
	$(CXX)  $(CXXFLAGS) $@.cpp router.cpp -o $@ $^


clean:
	rm -rf *.o *~ *.gch *.swp *.dSYM my-router  *.tar.gz

tarball: clean
	tar -cvf $(USERID).tar.gz *
