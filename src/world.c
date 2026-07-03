#include "world.h"
#include <time.h>
#include <stdlib.h>

Chunk generateChunk(void) {
    Chunk chunk;
    srand(time(NULL));

    for(int i = 0; i < CHUNK_SIZE_DEPTH; i++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                chunk.blocks[i][j][k] = rand() % 2;
            }
        }
    }

    return chunk;
}


void renderChunk(const Chunk* chunk, const RenderChunkCallback renderCallback) {
    for(int i = 0; i < CHUNK_SIZE_DEPTH; i++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                const Block* block = &chunk->blocks[i][j][k];
                const Coords3D coords = { k, j, i };
                renderCallback(&coords, block);
            }
        }
    }
}
