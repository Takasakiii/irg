#pragma once

#include <raylib.h>
#include "core.h"

Camera2D cameraSetup(const GameState* gameState);

void handlePlayerCameraControls(GameState* gameState);
