#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "value.h"

typedef enum {
  OP_CONSTANT,
  OP_CONSTANT_LONG,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t* code;
  int lines_count;
  int lines_capacity;
  int *lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte, int line);
uint8_t readChunk(Chunk* chunk, int index);
void freeChunk(Chunk* chunk);
int addConstant(Chunk* chunk, Value value);
int getLine(Chunk* chunk, int index);
void writeConstant(Chunk* chunk, Value value, int line);

#endif
