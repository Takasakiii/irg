#include "isometric.h"

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

void drawIsoCube(const Vector2* isoPos, const Vector3* blockSize) {
    const Vector2 top = { isoPos->x, isoPos->y };
    const Vector2 right = { isoPos-> x + blockSize->x / 2.0, isoPos->y + blockSize->y / 2.0 };
    const Vector2 bottom = { isoPos->x, isoPos->y + blockSize->y };
    const Vector2 left = { isoPos->x - blockSize->x / 2.0, isoPos->y + blockSize->y /2.0 };

    const Vector2 leftB = { left.x, left.y + blockSize->z };
    const Vector2 bottomB = { bottom.x, bottom.y + blockSize->z };
    const Vector2 rightB = { right.x, right.y + blockSize->z };

    const Vector2 topFace[] = { top, left, bottom, right };
    DrawTriangleFan(topFace, 4, GRAY);
    DrawLineStrip(topFace, 4, LIGHTGRAY);
    DrawLineV(right, top, BLACK);

    const Vector2 leftFace[] = { left, leftB, bottomB, bottom };
    DrawTriangleFan(leftFace, 4, GRAY);
    DrawLineStrip(leftFace, 4, LIGHTGRAY);

    const Vector2 rightFace[] = { bottom, bottomB, rightB, right };
    DrawTriangleFan(rightFace, 4, GRAY);
    DrawLineStrip(rightFace, 4, LIGHTGRAY);
}
