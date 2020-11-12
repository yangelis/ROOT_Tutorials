ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)
LIBS := -lMinuit -lRooFit -lRooFitCore

.SECONDEXPANSION:
.PHONY: all clean

all: 01_histo 02_roofit

01_histo: $$@.cpp
	$(CXX) -g $< -o $@ $(ROOTCXXFLAGS)

02_roofit: $$@.cpp
	$(CXX) -g $< -o $@ $(ROOTCXXFLAGS) $(LIBS)

clean: 
	rm -f 01_histo 02_roofit
