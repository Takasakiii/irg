#include "isometric.h"

#include <math.h>

Vector2 cartesianToIso(const Coords3D* catesian, const Size3D* blockSize) {
    Vector2 screenPos;
    screenPos.x = (catesian->x - catesian->y) * (blockSize->x / 2.0);
    screenPos.y = (catesian->x + catesian->y) * (blockSize->y / 2.0);

    screenPos.y -= (catesian->z * blockSize->z);

    return screenPos;
}

void drawIsoCube(const Coords3D* blockPos, const Size3D* blockSize, const Block* block,  bool enableDebug, bool enableLines) {
    const Color selectColor = BLACK;
    const Vector2 isoPos = cartesianToIso(blockPos, blockSize);

    const Vector2 top = { isoPos.x, isoPos.y };
    const Vector2 right = { isoPos.x + blockSize->x / 2.0, isoPos.y + blockSize->y / 2.0 };
    const Vector2 bottom = { isoPos.x, isoPos.y + blockSize->y };
    const Vector2 left = { isoPos.x - blockSize->x / 2.0, isoPos.y + blockSize->y /2.0 };

    const Vector2 leftB = { left.x, left.y + blockSize->z };
    const Vector2 bottomB = { bottom.x, bottom.y + blockSize->z };
    const Vector2 rightB = { right.x, right.y + blockSize->z };

    const Vector2 topFace[] = { top, left, bottom, right };

    const BlockColor blockColor = getBlockColor(block);

    DrawTriangleFan(topFace, 4, blockColor.topFace);
    if(enableLines) {
        DrawLineStrip(topFace, 4, selectColor);
        DrawLineV(right, top, selectColor);
    }

    const Vector2 leftFace[] = { left, leftB, bottomB, bottom };
    DrawTriangleFan(leftFace, 4, blockColor.body);
    if(enableLines) {
        DrawLineStrip(leftFace, 4, selectColor);
    }

    const Vector2 rightFace[] = { bottom, bottomB, rightB, right };
    DrawTriangleFan(rightFace, 4, blockColor.body);
    if(enableLines) {
        DrawLineStrip(rightFace, 4, selectColor);
    }

    if(enableDebug) {
        DrawText(TextFormat("(%d, %d, %d)", blockPos->x, blockPos->y, blockPos->z), isoPos.x, isoPos.y, 12, BLACK);
    }
}

bool isomentricIsMouseHover(const Camera2D camera, const Coords3D* blockPos, const Size3D* blockSize) {
    const Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);
    const Vector2 isoPos = cartesianToIso(blockPos, blockSize);

    const float isoX = isoPos.x;
    const float isoY = isoPos.y;

    const float dx = fabsf(mouse.x - isoX);
    const float dy = fabsf(mouse.y - (isoY + blockSize->y * 0.5f));

    const float hw = blockSize->x * 0.5f;
    const float hh = blockSize->y * 0.5f;

    return (dx / hw + dy / hh) <= 1.0f;
}
