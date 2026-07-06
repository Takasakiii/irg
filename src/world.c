#include "world.h"

#include <time.h>
#include <stdlib.h>
#include <string.h>


static int64_t coord_key(const Coords2D* chunkCoords) {
    return ((int64_t)(int32_t)chunkCoords->x << 32) | (int32_t)chunkCoords->y;
}

Chunk* generateChunk(const Coords2D* chunkCoords) {
    Chunk* chunk = malloc(sizeof(Chunk));
    srand(time(NULL));

    for(int i = 0; i < CHUNK_SIZE; i++) {
        for(int j = 0; j < CHUNK_SIZE_DEPTH; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                const bool existsBlock = rand() % 2;
                BlockType type;

                if (!existsBlock) {
                    type = NONE;
                } else if (j == CHUNK_SIZE_DEPTH - 1) {
                    type = GLASS;
                } else {
                    type = STONE;
                }

                chunk->blocks[i][j][k].type = type;
            }
        }
    }

    memcpy(&chunk->coords, chunkCoords, sizeof(Coords2D));
    return chunk;
}


void renderChunk(const GameState* gameState, const Chunk* chunk, const RenderChunkCallback renderCallback) {
    const Size2D* chunkSize = gameState->gridSize;
    const Coords2D* chunkCoords = &chunk->coords;
    for(int i = 0; i < gameState->gridSize->y; i++) {
        int yMin = gameState->cameraLayer - 3;
        if(yMin < 0) {
            yMin = 0;
        }

        for(int j = yMin; j < gameState->cameraLayer; j++) {
            for(int k = 0; k < gameState->gridSize->x; k++) {
                const Block* block = &chunk->blocks[i][j][k];
                const Coords3D coords = { (chunkCoords->x * chunkSize->x) + k, (chunkCoords->y * chunkSize->y) + i, j };
                renderCallback(&coords, block);
            }
        }
    }
}

BlockColor getBlockColor(const Block* block) {
    Color topFace;
    Color body;

    switch (block->type) {
    case NONE:
        topFace = (Color) {
            0, 0, 0, 0
        };
        body = topFace;
        break;
    case GLASS:
        body = LIME;
        topFace = GREEN;
        break;
    case STONE:
        topFace = LIGHTGRAY;
        body = GRAY;
        break;
    }

    return (BlockColor) {
        topFace,
        body
    };
}

World* generateWorld(const Size2D* size) {
    World* w = kh_init(world);

    for(int i = 0; i < size->y; i++) {
        for(int j = 0; j < size->x; j++) {
           const Coords2D ccoords = { j, i };
           const Chunk* chunk = generateChunk(&ccoords);
           int ret;
           khint_t iterator = kh_put(world, w, coord_key(&ccoords), &ret);
           kh_value(w, iterator) = (Chunk*)chunk;
        }
    }

    return w;
}

void destroyWorld(World* w) {
    for(khint_t iterator = kh_begin(world); iterator != kh_end(w); ++iterator) {
        if(!kh_exist(w, iterator)) continue;
        free(kh_val(w, iterator));
    }

    kh_destroy(world, w);
}


void renderWorld(const GameState* gameState, const World* w, const RenderChunkCallback renderCallback) {
    int minX = 0, maxX = 0, minY = 0, maxY = 0;
    bool first = true;
    for(khint_t iterator = kh_begin(w); iterator != kh_end(w); ++iterator) {
        if(!kh_exist(w, iterator)) continue;
        const Chunk* chunk = kh_val(w, iterator);
        if(first) {
            minX = maxX = chunk->coords.x;
            minY = maxY = chunk->coords.y;
            first = false;
        } else {
            if(chunk->coords.x < minX) minX = chunk->coords.x;
            if(chunk->coords.x > maxX) maxX = chunk->coords.x;
            if(chunk->coords.y < minY) minY = chunk->coords.y;
            if(chunk->coords.y > maxY) maxY = chunk->coords.y;
        }
    }

    for(int cy = minY; cy <= maxY; cy++) {
        for(int cx = minX; cx <= maxX; cx++) {
            const Coords2D cc = { cx, cy };
            khint_t iterator = kh_get(world, w, coord_key(&cc));
            if(iterator == kh_end(w)) continue;
            const Chunk* chunk = kh_val(w, iterator);
            renderChunk(gameState, chunk, renderCallback);
        }
    }
}
