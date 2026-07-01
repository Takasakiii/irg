#pragma once

#include <raylib.h>

Vector2 cartesianToIso(const Vector2* catesian, const Vector3* blockSize);

void drawIsoCube(const Vector2* isoPos, const Vector3* blockSize);
