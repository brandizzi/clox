CFLAGS=-I..
test: clox-test
	./clox-test

# Executable

clox-test: AllTests.o CuTest.o chunk_test.o chunk.o memory.o value.o
	cc $(CCFLAGS) -o $@ $^

# Test framework

AllTests.o: AllTests.c CuTest.h chunk_test.h
	cc $(CCFLAGS) -I.. -c -o $@ $<
CuTest.o: CuTest.c CuTest.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Tests

chunk_test.o: chunk_test.c chunk_test.h ../chunk.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Tested code

chunk.o: ../chunk.c ../chunk.h ../memory.h
	cc $(CCFLAGS) -I.. -c -o $@ $<
memory.o: ../memory.c ../memory.h
	cc $(CCFLAGS) -I.. -c -o $@ $<
value.o: ../value.c ../value.h
	cc $(CCFLAGS) -I.. -c -o $@ $<

# Cleanup

clean:
	rm *.o
