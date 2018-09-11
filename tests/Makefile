CFLAGS=-I..
test: clox-test
	./clox-test

# Executable

clox-test: AllTests.o CuTest.o chunk_test.o chunk.o memory.o value.o
	cc -o $@ $^

# Test framework

AllTests.o: AllTests.c CuTest.h chunk_test.h
	cc -I.. -c -o $@ $<
CuTest.o: CuTest.c CuTest.h
	cc -I.. -c -o $@ $<

# Tests

chunk_test.o: chunk_test.c chunk_test.h ../chunk.h
	cc -I.. -c -o $@ $<

# Tested code

chunk.o: ../chunk.c ../chunk.h ../memory.h
	cc -I.. -c -o $@ $<
memory.o: ../memory.c ../memory.h
	cc -I.. -c -o $@ $<
value.o: ../value.c ../value.h
	cc -I.. -c -o $@ $<

# Cleanup

clean:
	rm *.o
