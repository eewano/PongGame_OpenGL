#include "Input.hpp"
#include <iostream>

void Input::Update()
{
    for(size_t i = 0; i < KEY_MAX; i++)
    {
        mKeyStates[i].lastPressed = mKeyStates[i].pressed;
    }
}
