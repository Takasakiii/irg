#include "camera.h"
#include "isometric.h"

Camera2D cameraSetup(const CameraOptions cameraOptions) {
    return (Camera2D) {
        (Vector2) { cameraOptions.screenSize->x / 2.0, cameraOptions.screenSize->y / 2.0 }, // offset
        cartesianToIso(&(Vector2) { cameraOptions.gridSize->x / 2.0, cameraOptions.gridSize->y / 2.0 }, cameraOptions.blockSize), // target
        0.0, // rotation
        1.0 // zoom
    };
}


void handlePlayerCameraControls(Camera2D* camera) {
    const float velocity = 0.3;
    if(IsKeyDown(KEY_D)) camera->target.x += velocity;
    if(IsKeyDown(KEY_A)) camera->target.x -= velocity;
    if(IsKeyDown(KEY_W)) camera->target.y -= velocity;
    if(IsKeyDown(KEY_S)) camera->target.y += velocity;
}
