#include "camera.h"
#include "isometric.h"

Camera2D cameraSetup(const CameraOptions cameraOptions) {
    return (Camera2D) {
        (Vector2) { cameraOptions.screenSize->x / 2.0, cameraOptions.screenSize->y / 2.0 }, // offset
        cartesianToIso(&(Coords3D) { cameraOptions.gridSize->x / 2.0, cameraOptions.gridSize->y / 2.0, 0 }, cameraOptions.blockSize), // target
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
}
