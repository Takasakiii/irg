#include "camera.h"
#include "isometric.h"

Camera2D cameraSetup(const GameState* gameState) {
    const float worldSize = gameState->worldSize->x * gameState->gridSize->x;
    return (Camera2D) {
        (Vector2) { gameState->screenSize->x / 2.0, gameState->screenSize->y / 2.0 }, // offset
        cartesianToIso(&(Coords3D) {
            worldSize / 2.0,
            worldSize / 2.0,
            0.0
        }, gameState->blockSize), // target
        0.0, // rotation
        1.0 // zoom
    };
}


void handlePlayerCameraControls(GameState* gameState) {
    const float velocity = 150;
    const float frameTime = GetFrameTime();
    const float speed = velocity * frameTime;
    Camera2D* camera = gameState->camera;
    if(IsKeyDown(KEY_D)) camera->target.x += speed;
    if(IsKeyDown(KEY_A)) camera->target.x -= speed;
    if(IsKeyDown(KEY_W)) camera->target.y -= speed;
    if(IsKeyDown(KEY_S)) camera->target.y += speed;

    gameState->mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), *gameState->camera);
}
