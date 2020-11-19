ROOTCXXFLAGS  := $(shell root-config --cflags)
ROOTLIBS      := $(shell root-config --libs)
HEADERS       := myParticle.h



myVector: myVector.cpp libmyParticle.so
	$(CXX) $(ROOTCXXFLAGS) $< -lmyParticle -L. -Wl,-rpath,\$$ORIGIN -o $@ $(ROOTLIBS)

libmyParticle.so: MyDict.cxx
	$(CXX) -shared -fPIC $(ROOTCXXFLAGS) $^ -o $@

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ $(ROOTCXXFLAGS) $^

.PHONY: clean
clean:
	rm -f myVector; rm -f *.root; rm -f *.so;rm -f *.pcm; rm -f *.d;\
	rm MyDict.cxx
