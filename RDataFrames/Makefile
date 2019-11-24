ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)

.SECONDEXPANSION:
.PHONY: all clean


reading_root_files: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS)

writing_root_files: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS) $(LIBS)


all: reading_root_files writing_root_files

clean:
	@rm -f *.exe; rm -f *.root

