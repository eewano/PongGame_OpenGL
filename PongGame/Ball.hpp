#ifndef Ball_hpp
#define Ball_hpp

#include <iostream>
#include <stdio.h>
#include <time.h>
#include "Vec2.hpp"
#include "Define.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr float PI = 3.14159265358f;
static constexpr int BALL_VERTS_COUNT = 32;
static constexpr float BALL_RADIUS = 0.1f;

class Ball : public Sprite<BALL_VERTS_COUNT>
{
public:
    Ball(float aSize, float aDegree, float aSpeed);
    ~Ball();
    
    void SetVertex();
    void Move();
    void SwitchX();
    void SwitchY();
    void Restart();
    
private:
    Vec2f mMoveVec;
    float mDegree;
    float mSize;
    float mSpeed;
};

#endif /* Ball_hpp */
