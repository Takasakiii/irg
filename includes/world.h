#pragma once

#include <stdbool.h>
#include <raylib.h>
#include <khash.h>

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
    Block blocks[CHUNK_SIZE][CHUNK_SIZE_DEPTH][CHUNK_SIZE];
    Coords2D coords;
} Chunk;

typedef struct {
    const Color topFace;
    const Color body;
} BlockColor;

typedef void (*RenderChunkCallback)(const Coords3D*, const Block*) ;


KHASH_INIT(world, int64_t, Chunk*, true, kh_int64_hash_func, kh_int64_hash_equal)
typedef khash_t(world) World;

BlockColor getBlockColor(const Block* block);

World* generateWorld(const Size2D* size);

void destroyWorld(World* w);

void renderWorld(const GameState* gameState, const World* w, const RenderChunkCallback renderCallback);
