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
    Camera2D* camera;
    Size2D* screenSize;
    Size3D* blockSize;
    Size2D* gridSize;
    Size2D* worldSize;
    int cameraLayer;
    Vector2 mouseWorldPos;
} GameState;

Vector2 rotatePoint(Vector2 p, const Vector2* pivot, const float deg);
