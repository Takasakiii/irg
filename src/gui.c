#include "gui.h"

#include <raylib.h>
#include <math.h>

#include "world.h"

typedef void (*ButtonPressedCallback)(GameState* gameState) ;

static bool drawTriangleButton(GameState* gameState, Vector2 top, const float h, const float deg, Color color, ButtonPressedCallback callback) {
    const float l = ((2 * 1.73205) / 3.0) * h;
    const float ml = l / 2.0;
    const float b = top.y + h;

    Vector2 bl = {top.x - ml, b};
    Vector2 br = {top.x + ml, b};

    const Vector2 center = {
        (top.x + bl.x + br.x) / 3.0,
        (top.y + bl.y + br.y) / 3.0
    };

    top = rotatePoint(top, &center, deg);
    bl = rotatePoint(bl, &center, deg);
    br = rotatePoint(br, &center, deg);


    const Vector2 mousePos = GetMousePosition();

    const float minX = fminf(fminf(top.x, bl.x), br.x);
    const float maxX = fmaxf(fmaxf(top.x, bl.x), br.x);
    const float minY = fminf(fminf(top.y, bl.y), br.y);
    const float maxY = fmaxf(fmaxf(top.y, bl.y), br.y);

    bool inHover = false;

    if(mousePos.x >= minX && mousePos.x <= maxX && mousePos.y >= minY && mousePos.y <= maxY) {
        inHover = true;
    }

    if(inHover && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        color = RED;
    }

    if(inHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        callback(gameState);
    }

    DrawTriangle(top, bl, br, color);

    return inHover;
}

static void layerUpButtonHandle(GameState* gameState) {
    if(gameState->cameraLayer < CHUNK_SIZE_DEPTH) {
        gameState->cameraLayer++;
    }
}

static void layerDownButtonHandle(GameState* gameState) {
    if(gameState->cameraLayer > 1) {
        gameState->cameraLayer--;
    }
}

static void drawCameraControls(GameState* gameState, const Coords2D* position) {
    drawTriangleButton(gameState, (Vector2) {position->x, position->y - 55}, 50, 0, BLACK, layerUpButtonHandle);
    drawTriangleButton(gameState, (Vector2) {position->x, position->y + 5}, 50, 180, BLACK, layerDownButtonHandle);
}


void drawGui(GameState* gameState) {
    const Size2D* screenSize = gameState->screenSize;
    DrawText(TextFormat("FPS: %d", GetFPS()), 0, 0, 24, BLACK);
    drawCameraControls(gameState, &(Coords2D) {
        screenSize->x - 50,
        screenSize->y / 2.0
    });
}
