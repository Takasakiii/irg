#include "core.h"

#include <math.h>

Vector2 rotatePoint(Vector2 p, const Vector2* pivot, const float deg) {
    const float rad = deg * DEG2RAD;
    const float s = sinf(rad);
    const float c = cosf(rad);

    p.x -= pivot->x;
    p.y -= pivot->y;

    const Vector2 r = { p.x * c - p.y * s, p.x * s + p.y * c };

    return (Vector2) {
        r.x + pivot->x,
        r.y + pivot->y
    };
}
