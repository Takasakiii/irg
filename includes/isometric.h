#pragma once

#include <raylib.h>
#include <stdbool.h>

#include "core.h"
#include "world.h"

Vector2 cartesianToIso(const Coords3D* catesian, const IsoBlockMetrics* metrics);

void drawIsoCube(const Coords3D* blockPos, const IsoBlockMetrics* metrics, const Block* block,  bool enableDebug, bool enableLines);

bool isomentricIsMouseHover(const GameState* gameState, const Coords3D* blockPos);
