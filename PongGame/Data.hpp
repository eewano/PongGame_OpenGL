#ifndef Data_h
#define Data_h

struct Vec2
{
    float x, y;
    
public:
    Vec2() = default;
    
    Vec2(float a, float b)
    : x(a)
    , y(b)
    {
    }
    
    Vec2 operator*(float a)
    {
        return{x * a, y * a};
    }
};

static Vec2 WINDOW_SIZE = {800.0f, 600.0f};
static float ASPECT_RATIO = WINDOW_SIZE.x / WINDOW_SIZE.y;

#endif /* Data_h */
