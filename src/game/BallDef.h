#pragma once
#include "math/Vec3.h"

struct BallLevel {
    float radius;
    Vec3  tint;
    int   score;
};

inline const BallLevel kBallLevels[] = {
    { 0.3f, {1.0f, 0.2f, 0.2f}, 1  },
    { 0.5f, {1.0f, 0.5f, 0.0f}, 3  },
    { 0.7f, {1.0f, 1.0f, 0.0f}, 6  },
    { 0.9f, {0.2f, 0.8f, 0.2f}, 10 },
    { 1.1f, {0.2f, 0.2f, 1.0f}, 15 },
    { 1.4f, {0.5f, 0.0f, 0.5f}, 21 },
    { 1.7f, {1.0f, 0.0f, 0.5f}, 28 },
    { 2.1f, {0.2f, 0.8f, 0.8f}, 36 },
};
inline constexpr int kMaxBallLevel = 8;
