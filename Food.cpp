#include "Food.h"
#include <math.h>

Food::Food()
{
    this->randomize_position();
}

void Food::randomize_position()
{
    this->x_pos = rand()%GRID_WIDTH;
    this->y_pos = rand()%GRID_HEIGHT;
}

void Food::Draw()
{
    Rectangle rec = {this->x_pos*GRIDSIZE, this->y_pos*GRIDSIZE, GRIDSIZE, GRIDSIZE};
    DrawRectangleRec(rec, this->color);
    DrawRectangleRoundedLines(rec, 0.3f, 10, 5, BLACK);
}
