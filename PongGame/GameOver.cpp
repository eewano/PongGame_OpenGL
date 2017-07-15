#include "GameOver.hpp"

GameOver::GameOver(Vec2f aSize, Vec2f aPos)
{
    vertex[0] = geometry[0] = { -aSize.x / 2, +aSize.y / 2 };
    vertex[1] = geometry[1] = { +aSize.x / 2, +aSize.y / 2 };
    vertex[2] = geometry[2] = { +aSize.x / 2, -aSize.y / 2 };
    vertex[3] = geometry[3] = { -aSize.x / 2, -aSize.y / 2 };
    
    uv[0] = { 0.0f, 1.0f };
    uv[1] = { 1.0f, 1.0f };
    uv[2] = { 1.0f, 0.0f };
    uv[3] = { 0.0f, 0.0f };
    
    pos = aPos;
    size = aSize * 0.5f;
    
    for(size_t i = 0; i < 4; i++)
    {
        geometry[i] = pos + vertex[i];
    }
}

GameOver::~GameOver()
{
}

void GameOver::winLeft()
{
    pos.x = -0.5;
    pos.y = 0.25;
    
    for(size_t i = 0; i < 4; i++)
    {
        geometry[i] = pos + vertex[i];
    }
}

void GameOver::winRight()
{
    pos.x = 0.5;
    pos.y = 0.25;
    
    for(size_t i = 0; i < 4; i++)
    {
        geometry[i] = pos + vertex[i];
    }
}
