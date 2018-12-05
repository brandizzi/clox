OBJ := $(patsubst %.c,%.o,$(wildcard *.c))

clox: $(OBJ)
	cc $(CCFLAGS) -o $@ $(OBJ)

clox-test: chunk-test.o CuTest.o AllTests.o $(OBJ)
	cc $(CCFLAGS) -o $@ $< $(OBJ)

test:
	make -C tests test

%.o: %.c
	cc $(CCFLAGS) -c -o $@ $<

clean:
	rm $(OBJ)

