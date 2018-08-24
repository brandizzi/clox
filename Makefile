OBJ := $(patsubst %.c,%.o,$(wildcard *.c))

clox: $(OBJ)
	cc -o $@ $(OBJ)

%.o: %.c
	cc -c -o $@ $<

clean:
	rm $(OBJ)
