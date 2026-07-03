#pragma once

#include <stdbool.h>
#include <raylib.h>

#include "core.h"

enum {
    CHUNK_SIZE = 16,
    CHUNK_SIZE_DEPTH = 10
};

typedef enum {
    NONE,
    GLASS,
    STONE
} BlockType;

typedef struct {
    BlockType type;
} Block;

typedef struct {
    Block blocks[CHUNK_SIZE_DEPTH][CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

typedef struct {
    const Color topFace;
    const Color body;
} BlockColor;

typedef void (*RenderChunkCallback)(const Coords3D*, const Block*) ;


Chunk generateChunk(void);

void renderChunk(const Chunk* chunk, const RenderChunkCallback renderCallback);

BlockColor getBlockColor(const Block* block);
