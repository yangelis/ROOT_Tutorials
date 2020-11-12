ROOTCXXFLAGS := `root-config --cflags`
CXXFLAGS := ${ROOTCXXFLAGS} -Wall -ggdb -O0
LIBS := `root-config --ldflags --libs`

.PHONY: all
all: random_walk

%: %.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean:
	rm -f *.o random_walk
