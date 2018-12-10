#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

void initChunk(Chunk* chunk) {
  chunk->count = 0;
  chunk->capacity = 0;
  chunk->code = NULL;
  chunk->lines_count = 0;
  chunk->lines_capacity = 0;
  chunk->lines = NULL;
  initValueArray(&chunk->constants);
}

void writeChunk(Chunk* chunk, uint8_t byte, int line) {
  if (chunk->capacity < chunk->count + 1) {
    int oldCapacity = chunk->capacity;
    chunk->capacity = GROW_CAPACITY(oldCapacity);
    chunk->code = GROW_ARRAY(chunk->code, uint8_t,
        oldCapacity, chunk->capacity);
  }

  if (chunk->lines_capacity < chunk->lines_count + 1) {
    int oldCapacity = chunk->lines_capacity;
    chunk->lines_capacity = GROW_CAPACITY(oldCapacity);
    chunk->lines = GROW_ARRAY(chunk->lines, int,
      oldCapacity, chunk->lines_capacity);
  }

  chunk->code[chunk->count] = byte;
  chunk->count++;

  if (chunk->lines_count == 0) {
    chunk->lines[chunk->lines_count++] = chunk->count;
    chunk->lines[chunk->lines_count++] = line;
  } else if (chunk->lines[chunk->lines_count-1] == line) {
    chunk->lines[chunk->lines_count-2] = chunk->count;
  } else {
    chunk->lines[chunk->lines_count++] = chunk->count;
    chunk->lines[chunk->lines_count++] = line;
  }
}

uint8_t readChunk(Chunk* chunk, int index) {
  return chunk->code[index];
}

void freeChunk(Chunk* chunk) {
  FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
  FREE_ARRAY(int, chunk->lines, chunk->capacity);
  initChunk(chunk);
  freeValueArray(&chunk->constants);
}

int addConstant(Chunk* chunk, Value value) {
  writeValueArray(&chunk->constants, value);
  return chunk->constants.count - 1;
}

int getLine(Chunk* chunk, int offset) {
  for (int i = 0; i < chunk->lines_count; i+=2) {
    if (chunk->lines[i] > offset) {
      return chunk->lines[i+1];
    }
  }
  return -1;
}

void writeConstant(Chunk* chunk, Value value, int line) {
  writeChunk(chunk, OP_CONSTANT, line);
  int constant = addConstant(chunk, value);
  writeChunk(chunk, constant, line);
}

