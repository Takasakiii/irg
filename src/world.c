#include "world.h"
#include <time.h>
#include <stdlib.h>

Chunk generateChunk(void) {
    Chunk chunk;
    srand(time(NULL));

    for(int i = 0; i < CHUNK_SIZE_DEPTH; i++) {
        for(int j = 0; j < CHUNK_SIZE; j++) {
            for(int k = 0; k < CHUNK_SIZE; k++) {
                const bool existsBlock = rand() % 2;
                BlockType type;

                if (!existsBlock) {
                    type = NONE;
                } else if (i == CHUNK_SIZE_DEPTH - 1) {
                    type = GLASS;
                } else {
                    type = STONE;
                }

                chunk.blocks[i][j][k].type = type;
            }
        }
    }

    return chunk;
}


void renderChunk(const GameState* gameState, const Chunk* chunk, const RenderChunkCallback renderCallback) {
    for(int i = 0; i < gameState->cameraLayer; i++) {
        for(int j = 0; j < gameState->gridSize->y; j++) {
            for(int k = 0; k < gameState->gridSize->x; k++) {
                const Block* block = &chunk->blocks[i][j][k];
                const Coords3D coords = { k, j, i };
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
