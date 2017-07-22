#ifndef Define_h
#define Define_h

#include "Vec2.hpp"

static Vec2i WINDOW_SIZE = { 800, 600 };
static const float ASPECT_RATIO = static_cast<float>(WINDOW_SIZE.x) / WINDOW_SIZE.y;
static constexpr int INTERVAL = 60;
static constexpr int WIN_SCORE = 3;

#endif /* Define_h */
