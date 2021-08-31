#include "Snake.h"
#include <algorithm>

Snake::Snake(Sound deathSound)
{
    Vector2 tmp_pos = {GRID_WIDTH/2 * GRIDSIZE, GRID_HEIGHT/2 * GRIDSIZE};
    this->positions.push_back(tmp_pos);
    this->deathSound = deathSound;
}

void Snake::Draw()
{
    for(int i = (int)positions.size() - 1; i >= 0; i--)
    {
        float EyeSize = GRIDSIZE/3;
        Rectangle rec = {positions.at(i).x, positions.at(i).y, GRIDSIZE, GRIDSIZE};
        Color col = {std::clamp(255 - (i * 20), 50, 255), 37, 17, 255};
        DrawRectangleRounded(rec, 0.3f, 10, col);
        DrawRectangleRoundedLines(rec, 0.3f, 10, 5, BLACK);
        if(i == 0)
        {
            if(abs(direction.x))
            {
                if(direction.x == 1.0f)
                {
                    Rectangle r = {positions.at(i).x + GRIDSIZE - EyeSize, positions.at(i).y, EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/2, r.y + EyeSize/3, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                    r = {positions.at(i).x + GRIDSIZE - EyeSize, positions.at(i).y + (GRIDSIZE - EyeSize), EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/2, r.y + EyeSize/3, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                }else if(direction.x == -1.0f)
                {
                    Rectangle r = {positions.at(i).x, positions.at(i).y, EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x, r.y + EyeSize/3, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                    r = {positions.at(i).x, positions.at(i).y + (GRIDSIZE - EyeSize), EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x, r.y + EyeSize/3, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                }
            }
            if(abs(direction.y))
            {
                if(direction.y == 1.0f)
                {
                    Rectangle r = {(positions.at(i).x), positions.at(i).y + GRIDSIZE - EyeSize, EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/3.5, r.y + EyeSize/2, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                    r={(positions.at(i).x) + GRIDSIZE - EyeSize, positions.at(i).y + GRIDSIZE - EyeSize, EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/3.5, r.y + EyeSize/2, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                }else if(direction.y == -1.0f)
                {
                    Rectangle r = {(positions.at(i).x), positions.at(i).y , EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/3.5, r.y, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);
                    r={(positions.at(i).x) + GRIDSIZE - EyeSize, positions.at(i).y, EyeSize, EyeSize};
                    DrawRectangleRounded(r, 0.3f, 10, WHITE);
                    DrawRectangleRoundedLines(r, 0.3f, 10, 5, BLACK);
                    r = {r.x + EyeSize/3.5, r.y, EyeSize/2, EyeSize/2};
                    DrawRectangleRounded(r, 0.9f, 10, BLACK);

                }
            }   

        }
    }
 }


Vector2 Snake::get_head_position()
{
    return positions.front();
}

Vector2 Snake::get_pos()
{
    Vector2 tmp = {this->positions.front().x, this->positions.front().y};
    return tmp;
}

void Snake::move()
{
    Vector2 cur = this->get_head_position();
    Vector2 new_pos = {fmod((cur.x+direction.x*GRIDSIZE),GAME_WIDTH), fmod(cur.y+direction.y*GRIDSIZE, GAME_HEIGHT)};

    if (new_pos.x < 0)
        new_pos.x = GAME_WIDTH - GRIDSIZE;
    if (new_pos.y < 0)
        new_pos.y = GAME_HEIGHT - GRIDSIZE;

    for(int i = 0; i < this->positions.size(); i++)
    {
        if(new_pos.x == this->positions.at(i).x && new_pos.y == this->positions.at(i).y)
        {
            this->reset();
            return;
        }
    }
    
    this->positions.insert(this->positions.begin(), new_pos);
    if (this->positions.size() >= this->length)
        this->positions.pop_back();
}

void Snake::reset()
{
    PlaySound(this->deathSound);
    this->length = 1;
    this->positions.clear();
    Vector2 tmp_pos = {GRID_WIDTH/2 * GRIDSIZE, GRID_HEIGHT/2 * GRIDSIZE};
    this->positions.push_back(tmp_pos);
    this->score = 0;
}
