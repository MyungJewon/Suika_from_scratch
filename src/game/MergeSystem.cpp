#include "game/MergeSystem.h"
#include "event/EventBus.h"
#include "event/Events.h"
#include "game/BallComponent.h"
#include "game/BallDef.h"
#include "physics/Collider.h"
#include "physics/RigidBody.h"
#include "renderer/MeshRenderer.h"
#include "resource/MeshGenerator.h"
#include "scene/Transform.h"
#include <iostream>

MergeSystem::MergeSystem(GameState* state)
    : m_state(state) {
    EventBus::Subscribe<CollisionEvent>([this](const CollisionEvent& event) {
        if (m_reg == nullptr) return;
        if (pendingDestroy.count(event.a) > 0 || pendingDestroy.count(event.b) > 0) return;
        if (!m_reg->has<BallComponent>(event.a) || !m_reg->has<BallComponent>(event.b)) return;

        const BallComponent& ballA = m_reg->get<BallComponent>(event.a);
        const BallComponent& ballB = m_reg->get<BallComponent>(event.b);
        if (ballA.level != ballB.level) return;

        pendingMerges.push_back(MergeInfo{event.a, event.b, ballA.level, {0.0f, 0.0f, 0.0f}});
        pendingDestroy.insert(event.a);
        pendingDestroy.insert(event.b);
    });
}

void MergeSystem::update(Registry& reg, float) {
    m_reg = &reg;

    for (MergeInfo& merge : pendingMerges) {
        if (!reg.has<Transform>(merge.a) || !reg.has<Transform>(merge.b)) continue;
        if (!reg.has<BallComponent>(merge.a) || !reg.has<BallComponent>(merge.b)) continue;

        const Vec3 posA = reg.get<Transform>(merge.a).localPos;
        const Vec3 posB = reg.get<Transform>(merge.b).localPos;
        merge.midPos = (posA + posB) * 0.5f;

        reg.destroy(merge.a);
        reg.destroy(merge.b);

        const int newLevel = merge.level + 1;
        if (newLevel < kMaxBallLevel) {
            Entity entity = reg.create();

            Transform transform;
            transform.localPos = merge.midPos;
            reg.add<Transform>(entity, transform);

            m_generatedMeshes.push_back(MeshGenerator::CreateSphere(16, 16, kBallLevels[newLevel].radius));

            MeshRenderer renderer;
            renderer.mesh = &m_generatedMeshes.back();
            renderer.visible = true;
            renderer.material.tint = kBallLevels[newLevel].tint;
            renderer.material.albedo = nullptr;
            renderer.material.normalMap = nullptr;
            reg.add<MeshRenderer>(entity, renderer);

            RigidBody body;
            body.useGravity = true;
            body.mass = 1.0f;
            reg.add<RigidBody>(entity, body);

            Collider collider;
            collider.shape = ColliderShape::Sphere;
            collider.radius = kBallLevels[newLevel].radius;
            collider.restitution = 0.15f;
            collider.friction = 0.5f;
            reg.add<Collider>(entity, collider);

            reg.add<BallComponent>(entity, BallComponent{newLevel});
        }

        if (m_state != nullptr) {
            m_state->score += kBallLevels[merge.level].score;
        }
        std::cout << "[Merge] Level " << merge.level + 1
                  << " -> " << merge.level + 2
                  << "  Score: " << (m_state != nullptr ? m_state->score : 0) << "\n";
    }

    pendingMerges.clear();
    pendingDestroy.clear();
}
