ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)
LIBS := libmyParticle.so
HEADERS := myParticle.h


.SECONDEXPANSION:
.PHONY: clean


MyDict.cxx: $(HEADERS) Linkdef.h
	rootcint -f $@  $(CXXFLAGS)  $^

libmyParticle.so: MyDict.cxx
	g++ -shared -fPIC -o$@ `root-config --ldflags` $(CXXFLAGS) -std=c++17 -I$(ROOTSYS)/include $^

myVector: $$@.cpp
	$(CXX) -g $< -o $@.exe $(ROOTCXXFLAGS) $(LIBS)

clean:
	@rm -f *.exe; rm -f *.root; rm -f *.so;rm -f *.pcm; rm -f *.d
