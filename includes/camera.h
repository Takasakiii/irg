#pragma once

#include <raylib.h>

typedef struct {
    const Vector2* screenSize;
    const Vector2* gridSize;
    const Vector3* blockSize;
} CameraOptions;

Camera2D cameraSetup(const CameraOptions cameraOptions);

void handlePlayerCameraControls(Camera2D* camera);
