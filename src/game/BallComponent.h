#pragma once

struct BallComponent {
    int   level;        // 0-based (0~7)
    float age = 0.0f;  // 생성 후 경과 시간 (초)
};
