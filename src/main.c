#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "isometric.h"
#include "camera.h"
#include "world.h"


int main(void) {
    const int width = 720;
    const int height = 480;

    const Vector2 worldSize = { 100, 100 };

    InitWindow(width, height, "IRG");

    Block* world = malloc((sizeof(Block) * (int) worldSize.x) * (int)worldSize.y);

    const Vector3 blockSize = { 64.0, 32.0, 40.0 };

    Camera2D camera = cameraSetup((CameraOptions) {
        &(Vector2) { width, height }, //screenSize
        &worldSize,
        &blockSize
    });

    srand(time(NULL));
    for(int row = 0; row < (int) worldSize.y; row++) {
        for (int col = 0; col < (int) worldSize.x; col++) {
            world[(int)(worldSize.x * row + col)] = rand() % 2;
        }
    }

    while (!WindowShouldClose()) {
        handlePlayerCameraControls(&camera);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                for(int row = 0; row < (int) worldSize.y; row++) {
                    for (int col = 0; col < (int) worldSize.x; col++) {
                        if(world[(int)(worldSize.x * row + col)]) {
                            const Vector2 blockPos = {col, row};
                            const bool isMouseHover = isomentricIsMouseHover(camera, &blockPos, &blockSize);
                            drawIsoCube(&blockPos, &blockSize, false, isMouseHover);
                        }
                    }
                }
                // DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 24, BLACK);
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    free(world);
    return 0;
}
