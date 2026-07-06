#pragma once

#include <raylib.h>

typedef struct {
    const int x;
    const int y;
} Coords2D;

typedef struct {
    const int x;
    const int y;
    const int z;
} Coords3D;


typedef Coords2D Size2D;

typedef Coords3D Size3D;

typedef struct {
    float halfX;
    float halfY;
    float z;
} IsoBlockMetrics;

typedef struct {
    Camera2D* camera;
    const Size2D* screenSize;
    const Size3D* blockSize;
    const IsoBlockMetrics blockMetrics;
    const Size2D* gridSize;
    const Size2D* worldSize;
    int cameraLayer;
    Vector2 mouseWorldPos;
} GameState;

Vector2 rotatePoint(Vector2 p, const Vector2* pivot, const float deg);
