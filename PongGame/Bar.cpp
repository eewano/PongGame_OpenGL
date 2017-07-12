#include "Bar.hpp"

Bar::Bar(Vec2 aSize, Vec2 aPos)
{
    vertex[0] = geometry[0] = {-aSize.x / 2, +aSize.y / 2};
    vertex[1] = geometry[1] = {+aSize.x / 2, +aSize.y / 2};
    vertex[2] = geometry[2] = {+aSize.x / 2, -aSize.y / 2};
    vertex[3] = geometry[3] = {-aSize.x / 2, -aSize.y / 2};
    
    uv[0] = {0.0f, 1.0f};
    uv[1] = {1.0f, 1.0f};
    uv[2] = {1.0f, 0.0f};
    uv[3] = {0.0f, 0.0f};
    
    pos = aPos;
    size = aSize;
    
    for(size_t i = 0; i < BAR_VERTS_COUNT; i++)
    {
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
}

Bar::~Bar()
{
}

void Bar::MoveUp()
{
    Move(Vec2{0, +MOVE_SPEED});
}

void Bar::MoveDown()
{
    Move(Vec2{0, -MOVE_SPEED});
}

void Bar::Move(Vec2 aVec)
{
    pos.x += aVec.x;
    pos.y += aVec.y;
    
    if(pos.y > Y_LIMIT - vertex[0].y)
    {
        pos.y = Y_LIMIT - vertex[0].y;
    }
    
    if(pos.y < -Y_LIMIT + vertex[0].y)
    {
        pos.y = -Y_LIMIT + vertex[0].y;
    }
    
    for(size_t i = 0; i < BAR_VERTS_COUNT; i++)
    {
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
}

void Bar::Restart()
{
    pos.y = 0;
    
    for(size_t i = 0; i < BAR_VERTS_COUNT; i++)
    {
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
}
