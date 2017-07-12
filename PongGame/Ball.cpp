#include "Ball.hpp"

Ball::Ball(float aSize, float aDegree, float aSpeed)
: mDegree(aDegree)
, mSize(aSize)
, mSpeed(aSpeed)
, mMoveVec{static_cast<float>(sin(aDegree / 180.0f * PI)), static_cast<float>(cos(aDegree / 180.0f * PI))}
{
    SetVertex();
    size = {aSize, aSize};
}

Ball::~Ball()
{
}

void Ball::SetVertex()
{
    for(size_t i = 0; i < BALL_VERTS_COUNT; i++)
    {
        vertex[i].x = cos((float)i / BALL_VERTS_COUNT * PI * 2) * mSize;
        vertex[i].y = sin((float)i / BALL_VERTS_COUNT * PI * 2) * mSize;
        uv[i].x = cos((float)i / BALL_VERTS_COUNT * PI * 2) * 0.5f + 0.5f;
        uv[i].y = sin((float)i / BALL_VERTS_COUNT * PI * 2) * 0.5f + 0.5f;
        
        //ジオメトリの値を設定しておく
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
    std::srand((unsigned int)std::time(NULL));
}

void Ball::Move()
{
    pos.x += mMoveVec.x * mSpeed;
    pos.y += mMoveVec.y * mSpeed;
    
    const float BALL_X_LIMIT = 0.67f - mSize * 0.5;
    const float BALL_Y_LIMIT = 0.5f - mSize * 0.5;
    
    if(pos.x > BALL_X_LIMIT)
    {
        mMoveVec.x *= -1;
    }
    else if(pos.x < -BALL_X_LIMIT)
    {
        mMoveVec.x *= -1;
    }
    
    if(pos.y > BALL_Y_LIMIT)
    {
        mMoveVec.y *= -1;
    }
    else if(pos.y < -BALL_Y_LIMIT)
    {
        mMoveVec.y *= -1;
    }
    
    for(size_t i = 0; i < BALL_VERTS_COUNT; i++)
    {
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
}

void Ball::SwitchX()
{
    mMoveVec.x *= -1;
    mMoveVec.y = mMoveVec.y + ((rand() % 20 - 10) * 0.03);
}

void Ball::SwitchY()
{
    mMoveVec.y *= -1;
}

void Ball::Restart()
{
    mMoveVec.y = (rand() % 20 - 10) * 0.05;
    pos.x = 0;
    pos.y = 0;
    
    for(size_t i = 0; i < BALL_VERTS_COUNT; i++)
    {
        geometry[i].x = pos.x + vertex[i].x;
        geometry[i].y = pos.y + vertex[i].y;
    }
}
