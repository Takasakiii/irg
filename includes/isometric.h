#pragma once

#include <raylib.h>
#include <stdbool.h>

Vector2 cartesianToIso(const Vector2* catesian, const Vector3* blockSize);

void drawIsoCube(const Vector2* blockPos, const Vector3* blockSize, bool enableDebug, bool enableLines);

bool isomentricIsMouseHover(const Camera2D camera, const Vector2* blockPos, const Vector3* blockSize);
