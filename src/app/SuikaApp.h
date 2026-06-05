#pragma once

#include "app/Application.h"
#include "ecs/Entity.hpp"
#include "ecs/World.hpp"
#include "game/GameState.h"
#include "renderer/Renderer.h"
#include "resource/MeshGenerator.h"
#include "scene/Scene.h"
#include "systems/RenderSystem.h"
#include "systems/ScriptSystem.h"
#include "systems/TransformSystem.h"

class SuikaApp : public Application {
public:
    SuikaApp(int width, int height, const char* title);

protected:
    void OnInit() override;
    void OnUpdate(float dt) override;
    void OnFixedUpdate() override;
    void OnRender() override;

private:
    Entity CreateWall(const Vec3& position, const Vec3& halfExtents);
    Entity CreateBall(const Vec3& position, int levelIndex);

    Renderer m_renderer;
    Scene m_scene;
    World m_world;
    GameState m_state;
    Entity m_cameraEntity = NULL_ENTITY;
    Entity m_cursorEntity = NULL_ENTITY;
    Mesh m_boxMesh;
    Mesh m_ballMeshes[8];  // 레벨별 메쉬
    float m_cursorX = 0.0f;
    float m_dropCooldown = 0.0f;
    int   m_nextLevel = 0;  // 다음 드롭할 공 레벨
};
