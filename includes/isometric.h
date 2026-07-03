#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "core.h"
#include "world.h"

Vector2 cartesianToIso(const Coords3D* catesian, const Size3D* blockSize);

void drawIsoCube(const Coords3D* blockPos, const Size3D* blockSize, const Block* block,  bool enableDebug, bool enableLines);

bool isomentricIsMouseHover(const Camera2D camera, const Coords3D* blockPos, const Size3D* blockSize);
