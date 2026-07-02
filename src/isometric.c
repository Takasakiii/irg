#include "isometric.h"

#include <math.h>

Vector2 cartesianToIso(const Vector2* catesian, const Vector3* blockSize) {
    const float x = catesian->x;
    const float y = catesian->y;

    const float w = blockSize->x;
    const float h = blockSize->y;

    return (Vector2) {
        (x - y) * (w / 2.0),
        (x + y) * (h / 2.0)
    };
}

void drawIsoCube(const Vector2* blockPos, const Vector3* blockSize, bool enableDebug, bool enableLines) {
    const Color faceTopColor = LIGHTGRAY;
    const Color otherFacesColor = GRAY;
    const Color lineColor = BLACK;
    const Vector2 isoPos = cartesianToIso(blockPos, blockSize);

    const Vector2 top = { isoPos.x, isoPos.y };
    const Vector2 right = { isoPos.x + blockSize->x / 2.0, isoPos.y + blockSize->y / 2.0 };
    const Vector2 bottom = { isoPos.x, isoPos.y + blockSize->y };
    const Vector2 left = { isoPos.x - blockSize->x / 2.0, isoPos.y + blockSize->y /2.0 };

    const Vector2 leftB = { left.x, left.y + blockSize->z };
    const Vector2 bottomB = { bottom.x, bottom.y + blockSize->z };
    const Vector2 rightB = { right.x, right.y + blockSize->z };

    const Vector2 topFace[] = { top, left, bottom, right };
    DrawTriangleFan(topFace, 4, faceTopColor);
    if(enableLines) {
        DrawLineStrip(topFace, 4, lineColor);
        DrawLineV(right, top, lineColor);
    }

    const Vector2 leftFace[] = { left, leftB, bottomB, bottom };
    DrawTriangleFan(leftFace, 4, otherFacesColor);
    if(enableLines) {
        DrawLineStrip(leftFace, 4, lineColor);
    }

    const Vector2 rightFace[] = { bottom, bottomB, rightB, right };
    DrawTriangleFan(rightFace, 4, otherFacesColor);
    if(enableLines) {
        DrawLineStrip(rightFace, 4, lineColor);
    }

    if(enableDebug) {
        DrawText(TextFormat("(%d, %d)", (int)blockPos->x, (int)blockPos->y), isoPos.x, isoPos.y, 12, BLACK);
    }
}

bool isomentricIsMouseHover(const Camera2D camera, const Vector2* blockPos, const Vector3* blockSize) {
    const Vector2 mouse = GetScreenToWorld2D(GetMousePosition(), camera);
    const Vector2 isoPos = cartesianToIso(blockPos, blockSize);

    const float dx = fabsf(mouse.x - isoPos.x);
    const float dy = fabsf((float)(mouse.y - (isoPos.y + blockSize->y * 0.5)));

    const float hw = blockSize->x * 0.5;
    const float hh = blockSize->y * 0.5;

    return dx / hw + dy / hh <= 1.0;
}
