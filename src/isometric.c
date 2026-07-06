#include "isometric.h"

#include <math.h>

Vector2 cartesianToIso(const Coords3D* catesian, const IsoBlockMetrics* metrics) {
    Vector2 screenPos;
    screenPos.x = (catesian->x - catesian->y) * metrics->halfX;
    screenPos.y = (catesian->x + catesian->y) * metrics->halfY;

    screenPos.y -= (catesian->z * metrics->z);

    return screenPos;
}

void drawIsoCube(const Coords3D* blockPos, const IsoBlockMetrics* metrics, const Block* block,  bool enableDebug, bool enableLines) {
    const Color selectColor = BLACK;
    const Vector2 isoPos = cartesianToIso(blockPos, metrics);

    const Vector2 top = { isoPos.x, isoPos.y };
    const Vector2 right = { isoPos.x + metrics->halfX, isoPos.y + metrics->halfY };
    const Vector2 bottom = { isoPos.x, isoPos.y + (metrics->halfY * 2.0f) };
    const Vector2 left = { isoPos.x - metrics->halfX, isoPos.y + metrics->halfY };

    const Vector2 leftB = { left.x, left.y + metrics->z };
    const Vector2 bottomB = { bottom.x, bottom.y + metrics->z };
    const Vector2 rightB = { right.x, right.y + metrics->z };

    const Vector2 topFace[] = { top, left, bottom, right };

    const BlockColor blockColor = getBlockColor(block);

    DrawTriangleFan(topFace, 4, blockColor.topFace);

    const Vector2 leftFace[] = { left, leftB, bottomB, bottom };
    DrawTriangleFan(leftFace, 4, blockColor.body);

    const Vector2 rightFace[] = { bottom, bottomB, rightB, right };
    DrawTriangleFan(rightFace, 4, blockColor.body);

    if(enableLines) {
        DrawLineStrip(topFace, 4, selectColor);
        DrawLineV(right, top, selectColor);
        DrawLineStrip(leftFace, 4, selectColor);
        DrawLineStrip(rightFace, 4, selectColor);
    }

    if(enableDebug) {
        DrawText(TextFormat("(%d, %d, %d)", blockPos->x, blockPos->y, blockPos->z), isoPos.x, isoPos.y, 12, BLACK);
    }
}

bool isomentricIsMouseHover(const GameState* gameState, const Coords3D* blockPos) {
    if(blockPos->z != gameState->cameraLayer - 1) return false;

    const IsoBlockMetrics* metrics = &gameState->blockMetrics;
    const Vector2* mouse = &gameState->mouseWorldPos;
    const Vector2 isoPos = cartesianToIso(blockPos, metrics);

    const float isoX = isoPos.x;
    const float isoY = isoPos.y;

    const float dx = fabsf(mouse->x - isoX);
    const float dy = fabsf(mouse->y - (isoY + metrics->halfY));

    return (dx / metrics->halfX + dy / metrics->halfY) <= 1.0f;
}
