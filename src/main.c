#include <raylib.h>
#include <raymath.h>
#include <stdbool.h>

#include "isometric.h"

#define ENABLE_RANDOM 1

typedef bool Block;

int main(void) {
    const int width = 720;
    const int height = 480;

    const int gridW = 10;
    const int gridH = 10;

    InitWindow(width, height, "IRG");

    Block world[gridH][gridW];

    const Vector3 blockSize = { 64.0, 32.0, 40.0 };

    const Camera2D camera = {
        (Vector2) { width / 2.0, height / 2.0 }, // offset
        cartesianToIso(&(Vector2) { gridW / 2.0, gridH / 2.0 }, &blockSize), // target
        0.0, // rotation
        1.0 // zoom
    };

#if defined (ENABLE_RANDOM) && (ENABLE_RANDOM != 1)
    for(int row = 0; row < gridH; row++) {
        for (int col = 0; col < gridW; col++) {
            world[row][col] = true;
        }
    }
#endif

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
                for(int row = 0; row < gridH; row++) {
                    for (int col = 0; col < gridW; col++) {
                        if(world[row][col]) {
                            const Vector2 isoPos = cartesianToIso(&(Vector2) {col, row}, &blockSize);
                            drawIsoCube(&isoPos, &blockSize);
                        }
                    }
                }
                DrawCircleV(camera.target, 5, RED);
            EndMode2D();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
