ROOTCXXFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

.SECONDEXPANSION:
.PHONY: all clean


01_saveTrees: $$@.cpp
	$(CXX) $(ROOTCXXFLAGS) $< -o $@ ${ROOTLIBS}


02_readTrees: $$@.cpp
	$(CXX) $(ROOTCXXFLAGS) $< -o $@ ${ROOTLIBS}

all: 01_saveTrees 02_readTrees

clean: 
	@rm -f 01_saveTrees;rm -f 02_readTrees; rm -f *.root
