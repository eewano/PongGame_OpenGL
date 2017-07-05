#ifndef Score_h
#define Score_h

#include <iostream>

#include "Data.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int SCORE_VERTS_COUNT = 4;
static Vec2 SCORE_SIZE = {0.25f, 0.25f};

template<int VertsCount = 4>
class Score : public Sprite<SCORE_VERTS_COUNT>
{
public:
    Score(Vec2 aSize, Vec2 aPos)
    {
        static_assert(VertsCount == 4, "VertsCount == 4");
        vertex[0] = geometry[0] = {-aSize.x / 2, +aSize.y / 2};
        vertex[1] = geometry[1] = {+aSize.x / 2, +aSize.y / 2};
        vertex[2] = geometry[2] = {+aSize.x / 2, -aSize.y / 2};
        vertex[3] = geometry[3] = {-aSize.x / 2, -aSize.y / 2};
        
        RefreshUv(0);
        pos = aPos;
        size = aSize * 0.5f;
        
        for(size_t i = 0; i < 4; i++)
        {
            geometry[i].x = pos.x + vertex[i].x;
            geometry[i].y = pos.y + vertex[i].y;
        }
    }
    
    ~Score(){}
    
    void Update(int aNum)
    {
        mNum = aNum;
        RefreshUv(aNum);
    }
    
    void RefreshUv(int index)
    {
        uv[0] = {index / 10.0f, 1};
        uv[1] = {(index + 1) / 10.0f, 1};
        uv[2] = {(index + 1) / 10.0f, 0};
        uv[3] = {index / 10.0f, 0};
    }
    
    void RestartUv()
    {
        uv[0] = {0.0f, 1};
        uv[1] = {1 / 10.0f, 1};
        uv[2] = {1 / 10.0f, 0};
        uv[3] = {0.0f, 0};
    }
    
private:
    int mNum;
};

#endif /* Score_h */
