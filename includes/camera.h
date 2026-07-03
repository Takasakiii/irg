#pragma once

#include <raylib.h>
#include "core.h"

typedef struct {
    const Size2D* screenSize;
    const Size2D* gridSize;
    const Size3D* blockSize;
} CameraOptions;

Camera2D cameraSetup(const CameraOptions cameraOptions);

void handlePlayerCameraControls(GameState* gameState);
