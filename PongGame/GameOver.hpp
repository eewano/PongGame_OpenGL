#ifndef GameOver_h
#define GameOver_h

#include <iostream>

#include "Data.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int GAMEOVER_VERTS_COUNT = 4;
static Vec2 GAMEOVER_SIZE = {1.0f, 0.75f};
static Vec2 WIN_SIZE = {0.5f, 0.25f};
static Vec2 READY_SIZE = {0.8f, 0.4f};

template<int VertsCount = 4>
class GameOver : public Sprite<GAMEOVER_VERTS_COUNT>
{
public:
    GameOver(Vec2 aSize, Vec2 aPos)
    {
        static_assert(VertsCount == 4, "VertsCount == 4");
        vertex[0] = geometry[0] = {-aSize.x / 2, +aSize.y / 2};
        vertex[1] = geometry[1] = {+aSize.x / 2, +aSize.y / 2};
        vertex[2] = geometry[2] = {+aSize.x / 2, -aSize.y / 2};
        vertex[3] = geometry[3] = {-aSize.x / 2, -aSize.y / 2};
        
        uv[0] = {0.0f, 1.0f};
        uv[1] = {1.0f, 1.0f};
        uv[2] = {1.0f, 0.0f};
        uv[3] = {0.0f, 0.0f};
        
        pos = aPos;
        size = aSize * 0.5f;
        
        for(size_t i = 0; i < 4; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
    
    ~GameOver(){}
    
    void winLeft()
    {
        pos.x = -0.5;
        pos.y = 0.25;
        
        for(size_t i = 0; i < 4; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
    
    void winRight()
    {
        pos.x = 0.5;
        pos.y = 0.25;
        
        for(size_t i = 0; i < 4; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
};

#endif /* GameOver_h */
