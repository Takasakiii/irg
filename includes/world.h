#pragma once

#include <stdbool.h>

#include "core.h"

enum {
    CHUNK_SIZE = 16,
    CHUNK_SIZE_DEPTH = 10
};

typedef bool Block;

typedef struct {
    Block blocks[CHUNK_SIZE_DEPTH][CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

typedef void (*RenderChunkCallback)(const Coords3D*, const Block*) ;


Chunk generateChunk(void);

void renderChunk(const Chunk* chunk, const RenderChunkCallback renderCallback);
