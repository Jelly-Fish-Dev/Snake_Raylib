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
            Color col;
            if ((x+y)%2 == 0)
                col = DARKBLUE;
            else
                col = DARKGREEN;
            
            DrawRectangle((x*GRIDSIZE), (y*GRIDSIZE), GRIDSIZE, GRIDSIZE, col);
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
    SetMusicVolume(chubbyCat, 0.3f);

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
            drawGameGrid();
            food.Draw();
            snake.Draw();
            char *text;
            if (snake.get_pos().x == food.x_pos * GRIDSIZE && snake.get_pos().y == food.y_pos * GRIDSIZE)
            {
                food.randomize_position();
                snake.length += 1;
                snake.score += 1;
                PlaySound(pointSound);
            }
            sprintf(text, "Score: %d", snake.score);
            DrawText(text, 5, SCREEN_HEIGHT - TEXT_SIZE, TEXT_SIZE, WHITE);
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