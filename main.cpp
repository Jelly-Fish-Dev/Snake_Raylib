#include "raylib.h"
#include "Game.h"
#include "Snake.h"
#include "Food.h"
#include <iostream>
#include <vector>
#include <math.h>


void drawGameGrid()
{
    for(int x = 0; x < GRID_WIDTH; x++)
    {
        for(int y = 0; y < GRID_HEIGHT; y++)
        {
            DrawRectangleLines((x*GRIDSIZE), (y*GRIDSIZE), GRIDSIZE, GRIDSIZE, WHITE);
        }
    }
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Snake in Raylib");
    double prev_time = GetTime();
    Food food = Food();
    InitAudioDevice();
    Sound pointSound = LoadSound("resources/point.wav");
    Sound deathSound = LoadSound("resources/death.wav");
    Music chubbyCat = LoadMusicStream("resources/Chubby Cat.mp3");
    Snake snake = Snake(deathSound);
    SetMusicVolume(chubbyCat, 0.5f);

    PlayMusicStream(chubbyCat);

    while (!WindowShouldClose())
    {

        if (IsKeyPressed(KEY_RIGHT)) snake.direction = {1.0f, 0.0f};
        if (IsKeyPressed(KEY_LEFT)) snake.direction = {-1.0f, 0.0f};
        if (IsKeyPressed(KEY_UP)) snake.direction = {0, -1};
        if (IsKeyPressed(KEY_DOWN)) snake.direction = {0, 1};
        BeginDrawing();
        //std::cout << GAME_HEIGHT << std::endl;
            double now_time = GetTime();
            double dt = now_time - prev_time;
            if(dt >= 0.1){
                snake.move();
                prev_time = GetTime();
            }
            ClearBackground(BLACK);
            snake.Draw();
            food.Draw();
            drawGameGrid();
            char *text;
            if (snake.get_pos().x == food.x_pos * GRIDSIZE)
            {
                if (snake.get_pos().y == food.y_pos * GRIDSIZE)
                {
                    snake.length += 1;
                    snake.score += 1;
                    PlaySound(pointSound);
                    food.randomize_position();
                }
            }
            sprintf(text, "Score: %d     FPS:%i", snake.score, GetFPS());
            DrawText(text, 5, 440, 32, WHITE);
        EndDrawing();
        UpdateMusicStream(chubbyCat);

    }
    UnloadSound(pointSound);
    UnloadSound(deathSound);
    UnloadMusicStream(chubbyCat);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}