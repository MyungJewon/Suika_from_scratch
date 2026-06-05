#include "game/GameOverSystem.h"
#include "event/EventBus.h"
#include "event/Events.h"
#include "game/BallComponent.h"
#include "physics/RigidBody.h"
#include "scene/Transform.h"
#include <iostream>

GameOverSystem::GameOverSystem(GameState* state)
    : m_state(state) {
}

void GameOverSystem::update(Registry& reg, float dt) {
    if (m_state == nullptr || m_state->gameOver) return;

    for (auto [ball, transform, body] : reg.view<BallComponent, Transform, RigidBody>()) {
        ball.age += dt;
        // 생성 직후(1.5초 이내)는 판정 제외 — 드롭 위치가 y=7이라 즉시 오판정 방지
        if (ball.age < 1.5f) continue;
        if (transform.localPos.y > 6.5f && body.velocity.length() < 2.0f) {
            m_state->gameOver = true;
            EventBus::Emit(GameOverEvent{});
            std::cout << "=== GAME OVER === Final Score: " << m_state->score << "\n";
            return;
        }
    }
}
