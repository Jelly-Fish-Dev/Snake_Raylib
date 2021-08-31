#pragma once
#include "raylib.h"
#include <vector>
#include "math.h"
#include "Game.h"

class Snake{
public:
    Snake(Sound);
    Vector2 get_head_position();
    Vector2 get_pos();
    void turn();
    void move();
    void reset();
    void Draw();
    int score = 0;
    int length = 1;
    Vector2 direction = {1.0f, 0.0f};
private:
    std::vector <Vector2> positions;
    Color color = RED;
    Sound deathSound;
};