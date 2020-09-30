ROOTCXXFLAGS := $(shell root-config --cflags --glibs --ldflags)
LIBS := libmyParticle.so
HEADERS := myParticle.h


.SECONDEXPANSION:
.PHONY: clean

myVector: $$@.cpp libmyParticle.so
	$(CXX) -g $^ -o $@.exe $(ROOTCXXFLAGS) $(LIBS)

libmyParticle.so: MyDict.cxx
	$(CXX) -shared -fPIC -o $@ `root-config --ldflags --cflags` $^

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ $(CXXFLAGS) $^

clean:
	@rm -f *.exe; rm -f *.root; rm -f *.so;rm -f *.pcm; rm -f *.d
