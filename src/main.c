#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#include "isometric.h"
#include "camera.h"
#include "world.h"
#include "core.h"
#include "gui.h"


enum {
    SCREEN_WIDTH = 1080,
    SCREEN_HEIGHT = 720
};


GameState gameState = {
    NULL, // camera
    &(Size2D) { SCREEN_WIDTH, SCREEN_HEIGHT }, //screenSize
    &(Size3D) { 64, 32, 40 }, //blockSize
    &(Size2D) {CHUNK_SIZE, CHUNK_SIZE}, // gridSize
    CHUNK_SIZE_DEPTH // cameraLayer
};

static void renderGame(const Coords3D* coords, const Block* block) {
    if(block->type == NONE) return;
    const bool isMouseHover = isomentricIsMouseHover(&gameState, coords);
    const bool isDebugKeyPressed = IsKeyDown(KEY_P);
    drawIsoCube(coords, gameState.blockSize, block, isDebugKeyPressed, isMouseHover);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "IRG");

    Camera2D camera = cameraSetup((CameraOptions) {
        gameState.screenSize,
        gameState.gridSize,
        gameState.blockSize
    });

    gameState.camera = &camera;

    World* world = generateWorld(&(Size2D) {
        9,
        9
    });

    while (!WindowShouldClose()) {
        handlePlayerCameraControls(&gameState);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                // renderChunk(&gameState, &chunk, renderWorld);
                renderWorld(&gameState, world, renderGame);
            EndMode2D();
            drawGui(&gameState);
        EndDrawing();
    }

    destroyWorld(world);

    CloseWindow();
    return 0;
}
