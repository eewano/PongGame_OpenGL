#ifndef Sprite_hpp
#define Sprite_hpp

#include <iostream>
#include <linmath.h>

#include "Shader.hpp"
#include "Data.hpp"

extern Shader shader;

template<int I>
class Sprite
{
public:
    Sprite() = default;
    virtual ~Sprite() = default;
    
    mat4x4 m, p, mvp;
    
public:
    void Draw(GLuint texId)
    {
        mat4x4_identity(m);
        mat4x4_translate_in_place(m, pos.x, pos.y, 0);
        mat4x4_ortho(p, -ASPECT_RATIO, ASPECT_RATIO, -1.0f, 1.0f, 1.0f, -1.0f);
        mat4x4_mul(mvp, p, m);
        
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glUniformMatrix4fv(shader.mMvpLocation, 1, false, (const GLfloat*)mvp);
        //ここでShaderに値を渡しておかないと描画されない(今回はgeometryの値を渡していなかった)
        glVertexAttribPointer(shader.mPositionLocation, 2, GL_FLOAT, false, 0, geometry);
        glVertexAttribPointer(shader.mUvLocation, 2, GL_FLOAT, false, 0, uv);
        
        glBindTexture(GL_TEXTURE_2D, texId);
        glDrawArrays(GL_TRIANGLE_FAN, 0, I);
    }
    
public:
    Vec2 size{};
    Vec2 pos{};
    Vec2 vertex[I]{};
    Vec2 geometry[I]{};
    Vec2 uv[I]{};
};

#endif /* Sprite_hpp */
