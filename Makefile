SAMPLES := samples/cylon samples/blank
LIB := lib/libsense-hat.a
CXXFLAGS := -Isrc -Os

all: $(SAMPLES)

samples/blank: src/blank.cpp src/sense-hat.h $(LIB)
	 $(CXX) $(CXXFLAGS) -o samples/blank src/blank.cpp -Llib -lsense-hat

samples/cylon: src/cylon.cpp src/sense-hat.h $(LIB)
	$(CXX) $(CXXFLAGS) -o samples/cylon src/cylon.cpp -Llib -lsense-hat

$(LIB): src/sense-hat.o
	ar -cr $(LIB) $<

src/sense-hat.o: src/sense-hat.cpp src/sense-hat.h
	$(CXX) $(CXXFLAGS) -o $@ src/sense-hat.cpp

clean:
	rm -f $(SAMPLES)
	rm -f $(LIB)
