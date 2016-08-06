SAMPLES := samples/cylon samples/blank
LIB := lib/libsense-hat.a

all: $(SAMPLES)

samples/blank: src/blank.c src/sense-hat.h $(LIB)
	gcc -Isrc -Os -o samples/blank src/blank.c -Llib -lsense-hat

samples/cylon: src/cylon.c src/sense-hat.h $(LIB)
	gcc -Isrc -Os -o samples/cylon src/cylon.c -Llib -lsense-hat

$(LIB): src/sense-hat.o
	ar -cr $(LIB) $<

src/sense-hat.o: src/sense-hat.c src/sense-hat.h
	gcc -c -Isrc -Os -o $@ src/sense-hat.c

