#pragma once

#include "ecs/Entity.hpp"
#include "ecs/System.hpp"
#include "game/GameState.h"
#include "math/Vec3.h"
#include "resource/ObjLoader.h"
#include <deque>
#include <unordered_set>
#include <vector>

class MergeSystem : public ISystem {
public:
    explicit MergeSystem(GameState* state);

    void update(Registry& reg, float dt) override;

private:
    struct MergeInfo {
        Entity a;
        Entity b;
        int level;
        Vec3 midPos;
    };

    std::vector<MergeInfo> pendingMerges;
    std::unordered_set<Entity> pendingDestroy;
    GameState* m_state = nullptr;
    Registry* m_reg = nullptr;
    std::deque<Mesh> m_generatedMeshes;
};
