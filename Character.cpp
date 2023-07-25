#include "Character.h"
#include "raymath.h"

Character::Character()
{
    width = texture.width / maxFrame;
    height = texture.height;
}

void Character::setScreenPos(int winWidth, int winHeight)
{
    screenPos = {
        (float)winWidth / 2.0f - 4.0f * (0.5f * width),
        (float)winHeight / 2.0f - 4.0f * (0.5f * height)};
}

/*TICK FUNCTION*/
void Character::tick(float deltaTime)
{
    worldPosLastFrame = worldPos;
    /*MOVEMENT*/
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;

    if (Vector2Length(direction) != 0.0)
    {
        // set worldPos = worldPos + direction

        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));

        direction.x < 0.f ? facing = -1.f : facing = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    // UPDATE ANIMATION FRAME
    runningTime += deltaTime;
    if (runningTime >= updateTime)
    {
        frame++;
        runningTime = 0.f;
        if (frame > maxFrame)
            frame = 0;
    }
    // draw knight
    Rectangle source{frame * width, 0.f, facing * width, height};
    Rectangle dest{screenPos.x, screenPos.y, 4.f * width, 4.f * height};
    Vector2 origin{};
    DrawTexturePro(texture, source, dest, origin, 0.f, WHITE);
}

void Character::undoMovement() 
{
    worldPos = worldPosLastFrame;
}
