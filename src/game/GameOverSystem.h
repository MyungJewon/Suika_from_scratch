#pragma once

#include "ecs/System.hpp"
#include "game/GameState.h"

class GameOverSystem : public ISystem {
public:
    explicit GameOverSystem(GameState* state);

    void update(Registry& reg, float dt) override;

private:
    GameState* m_state = nullptr;
};
