ROOTCXXFLAGS := $(shell root-config --cflags)
ROOTLIBS     := $(shell root-config --glibs --ldflags)
LIBS         := -lMinuit -lRooFit -lRooFitCore # extra ROOT libraries to link with

.SECONDEXPANSION:
.PHONY: all clean

all: h01_histo h02_roofit

h01_histo: $$@.cpp
	$(CXX) $(ROOTCXXFLAGS) $< -o $@ $(ROOTLIBS)

h02_roofit: $$@.cpp
	$(CXX) $(ROOTCXXFLAGS) -g $< -o $@ $(ROOTLIBS) $(LIBS)

clean: 
	rm -f h01_histo h02_roofit
