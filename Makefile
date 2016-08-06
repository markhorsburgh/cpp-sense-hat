SAMPLES := samples/cylon
LIB := lib/libsense-hat.a

all: $(SAMPLES)

samples/cylon: src/cylon.c src/sense-hat.h $(LIB)
	gcc -Isrc -Os -o samples/cylon src/cylon.c -Llib -lsense-hat

$(LIB): src/sense-hat.o
	ar -cq $(LIB) $<

src/sense-hat.o: src/sense-hat.c src/sense-hat.h
	gcc -c -Isrc -Os -o $@ src/sense-hat.c

