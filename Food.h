#pragma once
#include "Game.h"
#include "raylib.h"

class Food{
public:
    Food();
    void Draw();
    void randomize_position();
    int x_pos = 1;
    int y_pos = 1; 
private:
    Color color = {253,174,97, 255};
};