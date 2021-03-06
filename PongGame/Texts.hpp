#ifndef Texts_hpp
#define Texts_hpp

#include <iostream>
#include "Vec2.hpp"
#include "Define.hpp"
#include "Shader.hpp"
#include "Sprite.hpp"

static constexpr int GAMEOVER_VERTS_COUNT = 4;
static Vec2f GAMEOVER_SIZE = { 1.0f, 0.75f };
static Vec2f WIN_SIZE = { 0.5f, 0.25f };
static Vec2f READY_SIZE = { 0.8f, 0.4f };

class Texts : public Sprite<GAMEOVER_VERTS_COUNT>
{
public:
    Texts(Vec2f aSize, Vec2f aPos);
    ~Texts();
    
    void winLeft();
    void winRight();
};

#endif /* Texts_hpp */
