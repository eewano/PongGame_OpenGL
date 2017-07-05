#ifndef Input_hpp
#define Input_hpp

struct KeyState
{
    bool pressed;
    bool lastPressed;
};

class Input
{
public:
    static constexpr int KEY_MAX = 512;
    
    void Update();
    
public:
    KeyState mKeyStates[KEY_MAX];
};

#endif /* Input_hpp */
