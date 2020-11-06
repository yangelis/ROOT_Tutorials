ROOTCXXFLAGS	:= $(shell root-config --cflags)
ROOTLIBS			:= $(shell root-config --libs)
HEADERS				:= myParticle.h


.SECONDEXPANSION:
.PHONY: clean

myVector: $$@.cpp libmyParticle.so
	$(CXX) $(ROOTCXXFLAGS) $@.cpp libmyParticle.so -o $@ $(ROOTLIBS)

libmyParticle.so: MyDict.cxx
	#$(CXX) -shared -fPIC $(ROOTCXXFLAGS) $^ -o $@ $(ROOTLIBS)
	$(CXX) -shared -fPIC $(ROOTCXXFLAGS) $^ -o $@

MyDict.cxx: $(HEADERS) Linkdef.h
	rootcling -f $@ $(ROOTCXXFLAGS) $^

clean:
	rm -f myVector; rm -f *.root; rm -f *.so;rm -f *.pcm; rm -f *.d;\
	rm MyDict.cxx
