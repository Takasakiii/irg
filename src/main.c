#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#include "isometric.h"
#include "camera.h"
#include "world.h"
#include "core.h"

enum {
    SCREEN_WIDTH = 1080,
    SCREEN_HEIGHT = 720
};


Camera2D camera;
const Size3D blockSize = { 64, 32, 40 };

static void renderWorld(const Coords3D* coords, const Block* block) {
    if(block->type == NONE) return;
    const bool isMouseHover = isomentricIsMouseHover(camera, coords, &blockSize);
    const bool isDebugKeyPressed = IsKeyDown(KEY_P);
    drawIsoCube(coords, &blockSize, block, isDebugKeyPressed, isMouseHover);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "IRG");


    camera = cameraSetup((CameraOptions) {
        &(Size2D) { SCREEN_WIDTH, SCREEN_HEIGHT }, //screenSize
        &(Size2D) {CHUNK_SIZE, CHUNK_SIZE },
        &blockSize
    });

    const Chunk chunk = generateChunk();

    while (!WindowShouldClose()) {
        handlePlayerCameraControls(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                renderChunk(&chunk, renderWorld);
            EndMode2D();
            DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 24, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
