/**
 * Author: Klaus Holder
 * Date: 7/23/23
 * Game: CLASSY CLASH (NAME TBD)
 */

#include "raylib.h"
#include "raymath.h"
#include "Character.h"

/*CENTER WINDOW*/
void centerWindow(float w, float h)
{
    int monitor = GetCurrentMonitor();
    int mWidth = GetMonitorWidth(monitor);
    int mHeight = GetMonitorHeight(monitor);
    SetWindowPosition((int)(mWidth / 2) - (int)(w / 2), (int)(mHeight / 2) - (int)(h / 2));
}

/*MAIN FUNCTION*/
int main()
{
    const int windowWidth{384};
    const int windowHeight{384};
    InitWindow(windowWidth, windowHeight, "Klaus's RPG Adventure");
    Texture2D map = LoadTexture("nature_tileset/worldmap32x32.png");
    Vector2 mapPos{0.0, 0.0};
    const float mapScale{4.f};

    // center game window on screen
    centerWindow(windowWidth, windowHeight);

    Character knight;
    knight.setScreenPos(windowWidth, windowHeight);

    /*MAIN GAME WHILE LOOP*/
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        mapPos = Vector2Scale(knight.getWorldPos(), -1.f);

        // draw map
        DrawTextureEx(map, mapPos, 0.f, 4.f, WHITE);
        knight.tick(GetFrameTime());

        //Check map bounds
        if (knight.getWorldPos().x < 0.f ||
            knight.getWorldPos().y < 0.f ||
            knight.getWorldPos().x + windowWidth > map.width * mapScale ||
            knight.getWorldPos().y + windowHeight > map.height * mapScale)
            {
                knight.undoMovement();
            }

        EndDrawing();
    }
    UnloadTexture(map);
    CloseWindow();
}