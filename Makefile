OBJ := $(patsubst %.c,%.o,$(wildcard *.c))

clox: $(OBJ)
	cc -o $@ $(OBJ)

clox-test: chunk-test.o CuTest.o AllTests.o $(OBJ)
	cc -o $@ $< $(OBJ)

%.o: %.c
	cc -c -o $@ $<

clean:
	rm $(OBJ)

