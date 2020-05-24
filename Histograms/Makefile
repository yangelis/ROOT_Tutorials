ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)
LIBS := -lMinuit -lRooFit -lRooFitCore

.SECONDEXPANSION:
.PHONY: all clean


01_histo: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS)

02_roofit: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS) $(LIBS)


all: 01_histo 02_roofit

clean: 
	@rm -f *.exe 
