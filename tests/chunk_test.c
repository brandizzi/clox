#include "chunk.h"

#include "CuTest.h"

void testGetLine(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  writeChunk(&chunk, OP_RETURN, 123);

  CuAssertIntEquals(tc, 123, getLine(&chunk, 0));

  freeChunk(&chunk);
}

void testGetTwoCommands(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_RETURN, 456);
  writeChunk(&chunk, OP_CONSTANT, 123);

  CuAssertIntEquals(tc, 456, getLine(&chunk, 0));
  CuAssertIntEquals(tc, 123, getLine(&chunk, 1));

  freeChunk(&chunk);
}

void testGetManyCommands(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, OP_RETURN, 456);
  writeChunk(&chunk, OP_RETURN, 456);
  writeChunk(&chunk, OP_RETURN, 456);
  writeChunk(&chunk, OP_RETURN, 456);

  CuAssertIntEquals(tc, 123, getLine(&chunk, 0));
  CuAssertIntEquals(tc, 123, getLine(&chunk, 1));
  CuAssertIntEquals(tc, 123, getLine(&chunk, 2));
  CuAssertIntEquals(tc, 123, getLine(&chunk, 3));
  CuAssertIntEquals(tc, 456, getLine(&chunk, 4));
  CuAssertIntEquals(tc, 456, getLine(&chunk, 5));
  CuAssertIntEquals(tc, 456, getLine(&chunk, 6));
  CuAssertIntEquals(tc, 456, getLine(&chunk, 7));

  freeChunk(&chunk);
}

void testGetTwoCommandsOneLine(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_RETURN, 123);
  writeChunk(&chunk, OP_CONSTANT, 123);

  CuAssertIntEquals(tc, 123, getLine(&chunk, 0));
  CuAssertIntEquals(tc, 123, getLine(&chunk, 1));

  freeChunk(&chunk);
}

void testReadChunk(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);
  writeChunk(&chunk, OP_RETURN, 456);

  CuAssertIntEquals(tc, OP_CONSTANT, readChunk(&chunk, 0));
  CuAssertIntEquals(tc, constant, readChunk(&chunk, 1));
  CuAssertIntEquals(tc, OP_RETURN, readChunk(&chunk, 2));

  freeChunk(&chunk);
}

void testWriteConstant(CuTest *tc) {
  Chunk chunk;
  initChunk(&chunk);

  writeConstant(&chunk, 1.2, 123);
  writeConstant(&chunk, 1.2, 123);
  writeChunk(&chunk, OP_RETURN, 123);

  CuAssertIntEquals(tc, OP_CONSTANT, readChunk(&chunk, 0));
  CuAssertIntEquals(tc, 0, readChunk(&chunk, 1));
  CuAssertIntEquals(tc, OP_CONSTANT, readChunk(&chunk, 2));
  CuAssertIntEquals(tc, 1, readChunk(&chunk, 3));
  CuAssertIntEquals(tc, OP_RETURN, readChunk(&chunk, 4));

  freeChunk(&chunk);
}

CuSuite* ChunkGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, testGetLine);
  SUITE_ADD_TEST(suite, testGetTwoCommands);
  SUITE_ADD_TEST(suite, testGetTwoCommandsOneLine);
  SUITE_ADD_TEST(suite, testReadChunk);
  SUITE_ADD_TEST(suite, testWriteConstant);
  return suite;
}
