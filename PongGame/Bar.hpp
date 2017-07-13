#ifndef Bar_hpp
#define Bar_hpp

#include <iostream>

#include "Define.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int BAR_VERTS_COUNT = 4;
static constexpr float BAR_WIDTH = 0.1f;
static constexpr float BAR_LENGTH = 0.6f;
static Vec2 BAR_SIZE = { BAR_WIDTH, BAR_LENGTH };

class Bar : public Sprite<BAR_VERTS_COUNT>
{
public:
    static constexpr float MOVE_SPEED = 0.01f;
    static constexpr float Y_LIMIT = 0.5f + BAR_LENGTH / 4;
public:
    Bar(Vec2 aSize, Vec2 aPos);
    ~Bar();
    
    void MoveUp();
    void MoveDown();
    void Move(Vec2 aVec);
    void Restart();
};

#endif /* Bar_hpp */
