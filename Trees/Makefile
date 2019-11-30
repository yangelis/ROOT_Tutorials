ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)

.SECONDEXPANSION:
.PHONY: all clean


01_saveTrees: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS)



all: 01_saveTrees 

clean: 
	@rm -f *.exe; rm -f *.root