SAMPLES := samples/cylon samples/blank
LIB := lib/libsense-hat.a

all: $(SAMPLES)

samples/blank: src/blank.cpp src/sense-hat.h $(LIB)
	g++ -Isrc -Os -o samples/blank src/blank.cpp -Llib -lsense-hat

samples/cylon: src/cylon.cpp src/sense-hat.h $(LIB)
	g++ -Isrc -Os -o samples/cylon src/cylon.cpp -Llib -lsense-hat

$(LIB): src/sense-hat.o
	ar -cr $(LIB) $<

src/sense-hat.o: src/sense-hat.cpp src/sense-hat.h
	g++ -c -Isrc -Os -o $@ src/sense-hat.cpp

