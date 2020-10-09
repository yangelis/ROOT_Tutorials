ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)
HEADERS := myParticle.h


.SECONDEXPANSION:
.PHONY: clean

myVector: $$@.cpp libmyParticle.so
	$(CXX) -g $@.cpp libmyParticle.so -o $@ $(ROOTCXXFLAGS)

libmyParticle.so: MyDict.cxx
	$(CXX) -shared -fPIC -o $@ `root-config --ldflags --cflags` $^

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ $(CXXFLAGS) $^

clean:
	@rm -f myVector; rm -f *.root; rm -f *.so;rm -f *.pcm; rm -f *.d
