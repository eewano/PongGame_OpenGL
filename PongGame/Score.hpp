#ifndef Score_h
#define Score_h

#include <iostream>
#include "Vec2.hpp"
#include "Define.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int SCORE_VERTS_COUNT = 4;
static Vec2f SCORE_SIZE = { 0.15f, 0.2f };

class Score : public Sprite<SCORE_VERTS_COUNT>
{
public:
    Score(Vec2f aSize, Vec2f aPos);
    
    ~Score();
    
    void Update(int aNum);
    void RefreshUv(int index);
    void RestartUv();
    
private:
    int mNum;
};

#endif /* Score_h */
