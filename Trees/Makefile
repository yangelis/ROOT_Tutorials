ROOTCXXFLAGS := $(shell root-config --cflags)
ROOTLIBS := $(shell root-config --libs)

.SECONDEXPANSION:
.PHONY: all clean


01_saveTrees: $$@.cpp
	$(CXX) $(ROOTCXXFLAGS) $< -o $@ ${ROOTLIBS}



all: 01_saveTrees 

clean: 
	@rm -f 01_saveTrees; rm -f *.root
