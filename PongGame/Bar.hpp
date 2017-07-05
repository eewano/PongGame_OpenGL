#ifndef Bar_hpp
#define Bar_hpp

#include <iostream>

#include "Data.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int BAR_VERTS_COUNT = 4;
static constexpr float BAR_WIDTH = 0.1f;
static constexpr float BAR_LENGTH = 0.6f;
static Vec2 BAR_SIZE = {BAR_WIDTH, BAR_LENGTH};

template<int VertsCount = 4>
class Bar : public Sprite<BAR_VERTS_COUNT>
{
public:
    static constexpr float MOVE_SPEED = 0.01f;
    static constexpr float Y_LIMIT = 0.5f + BAR_LENGTH / 4;
public:
    Bar(Vec2 aSize, Vec2 aPos)
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
        
        for(size_t i = 0; i < VertsCount; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
    
    ~Bar(){}
    
    void MoveUp()
    {
        Move(Vec2{0, +MOVE_SPEED});
    }
    
    void MoveDown()
    {
        Move(Vec2{0, -MOVE_SPEED});
    }
    
    void Move(Vec2 aVec)
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
        
        for(size_t i = 0; i < VertsCount; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
    void Restart()
    {
        pos.y = 0;
        
        for(size_t i = 0; i < VertsCount; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
};

#endif /* Bar_hpp */
