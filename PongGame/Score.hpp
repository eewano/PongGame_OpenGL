#ifndef Score_h
#define Score_h

#include <iostream>
#include "Define.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int SCORE_VERTS_COUNT = 4;
static Vec2 SCORE_SIZE = {0.2f, 0.2f};

class Score : public Sprite<SCORE_VERTS_COUNT>
{
public:
    Score(Vec2 aSize, Vec2 aPos);
    
    ~Score();
    
    void Update(int aNum);
    void RefreshUv(int index);
    void RestartUv();
    
private:
    int mNum;
};

#endif /* Score_h */
