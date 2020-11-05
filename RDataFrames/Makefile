ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)

.SECONDEXPANSION:
.PHONY: all clean

all: reading_root_files writing_root_files

reading_root_files: $$@.cpp
	$(CXX) -g $< -o $@ $(ROOTCXXFLAGS)

writing_root_files: $$@.cpp
	$(CXX) -g $< -o $@ $(ROOTCXXFLAGS) $(LIBS)

clean:
	rm -f reading_root_files writing_root_files; rm -f *.root
