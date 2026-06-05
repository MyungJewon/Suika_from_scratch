#include "app/SuikaApp.h"
#include <random>
#include "event/EventBus.h"
#include "event/Events.h"
#include "game/BallComponent.h"
#include "game/BallDef.h"
#include "game/GameOverSystem.h"
#include "game/MergeSystem.h"
#include "input/InputManager.h"
#include "physics/Collider.h"
#include "physics/RigidBody.h"
#include "renderer/MeshRenderer.h"
#include "scene/Camera.h"
#include "scene/Light.h"
#include "scene/Transform.h"
#include "systems/CollisionSystem.h"
#include "systems/InputSystem.h"
#include "systems/PhysicsSystem.h"
#include <algorithm>
#include <iostream>

namespace {
Mesh CreateBoxMesh() {
    Mesh mesh;
    mesh.vertices = {
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}, {-1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f, -1.0f,  1.0f}, {1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f,  1.0f,  1.0f}, {1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, 1.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, -1.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, -1.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, -1.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}, {0.0f, 0.0f, -1.0f}},
        {{-1.0f,  1.0f,  1.0f}, {0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f,  1.0f}, {1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f,  1.0f, -1.0f}, {1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f,  1.0f, -1.0f}, {0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f, -1.0f}, {1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{ 1.0f, -1.0f,  1.0f}, {1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
        {{-1.0f, -1.0f,  1.0f}, {0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}, {1.0f, 0.0f, 0.0f}},
    };
    mesh.indices = {
         0,  1,  2,  0,  2,  3,
         4,  5,  6,  4,  6,  7,
         8,  9, 10,  8, 10, 11,
        12, 13, 14, 12, 14, 15,
        16, 17, 18, 16, 18, 19,
        20, 21, 22, 20, 22, 23
    };
    return mesh;
}
}

SuikaApp::SuikaApp(int width, int height, const char* title)
    : Application(width, height, title)
    , m_renderer(width, height)
    , m_world(m_scene.GetRegistry()) {
}

void SuikaApp::OnInit() {
    EventBus::Subscribe<GameOverEvent>([this](const GameOverEvent&) {
        RequestQuit();
        std::cout << "Final Score: " << m_state.score << "\n";
    });

    m_cameraEntity = m_scene.CreateEntity();
    Camera camera;
    camera.eye = { 0.0f, 0.0f, 20.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.aspect = GetWindow().Width() / static_cast<float>(GetWindow().Height());
    m_scene.GetRegistry().add<Camera>(m_cameraEntity, camera);
    m_scene.SetActiveCamera(m_cameraEntity);

    Entity lightEntity = m_scene.CreateEntity();
    Light light;
    light.position = { 0.0f, 7.0f, 8.0f };
    light.color = { 1.0f, 1.0f, 1.0f };
    light.ambient = 0.2f;
    light.diffuse = 0.8f;
    light.specular = 0.35f;
    light.shininess = 32.0f;
    m_scene.GetRegistry().add<Light>(lightEntity, light);
    m_scene.SetActiveLight(lightEntity);

    m_boxMesh = CreateBoxMesh();
    for (int i = 0; i < 8; i++)
        m_ballMeshes[i] = MeshGenerator::CreateSphere(16, 16, kBallLevels[i].radius);

    // 첫 번째 드롭 레벨 랜덤 결정
    {
        static std::mt19937 rng(std::random_device{}());
        static std::discrete_distribution<int> dist({4, 3, 2, 1});
        m_nextLevel = dist(rng);
    }

    CreateWall({ 0.0f, -6.0f, 0.0f }, { 4.2f, 0.2f, 1.0f });
    CreateWall({ -4.0f, 0.0f, 0.0f }, { 0.2f, 6.0f, 1.0f });
    CreateWall({ 4.0f, 0.0f, 0.0f }, { 0.2f, 6.0f, 1.0f });

    m_cursorEntity = m_scene.CreateEntity();
    MeshRenderer cursorRenderer;
    cursorRenderer.mesh = &m_ballMeshes[m_nextLevel];
    cursorRenderer.visible = true;
    cursorRenderer.material.tint = kBallLevels[m_nextLevel].tint;
    cursorRenderer.material.albedo = nullptr;
    cursorRenderer.material.normalMap = nullptr;
    Transform cursorTransform;
    cursorTransform.localPos = { m_cursorX, 7.0f, 0.0f };
    m_scene.GetRegistry().add<Transform>(m_cursorEntity, cursorTransform);
    m_scene.GetRegistry().add<MeshRenderer>(m_cursorEntity, cursorRenderer);

    m_world.add_system<InputSystem>();
    m_world.add_system<ScriptSystem>();
    m_world.add_system<MergeSystem>(&m_state);
    m_world.add_system<GameOverSystem>(&m_state);
    m_world.add_system<TransformSystem>();
    m_world.add_system<RenderSystem>(m_renderer, m_scene, GetWindow());
    m_world.add_fixed_system<PhysicsSystem>();
    m_world.add_fixed_system<CollisionSystem>();
}

void SuikaApp::OnUpdate(float dt) {
    InputManager& input = InputManager::Get();

    float direction = 0.0f;
    if (input.IsKeyDown(KeyCode::Left)) direction -= 1.0f;
    if (input.IsKeyDown(KeyCode::Right)) direction += 1.0f;

    m_cursorX = std::clamp(m_cursorX + direction * 5.0f * dt, -3.5f, 3.5f);
    if (m_cursorEntity != NULL_ENTITY && m_scene.GetRegistry().has<Transform>(m_cursorEntity)) {
        Transform& cursorTransform = m_scene.GetRegistry().get<Transform>(m_cursorEntity);
        cursorTransform.SetLocalPos({ m_cursorX, 7.0f, 0.0f }, m_scene.GetRegistry());
    }

    if (m_dropCooldown > 0.0f) {
        m_dropCooldown = std::max(0.0f, m_dropCooldown - dt);
    }

    if (input.JustPressed(KeyCode::Space) && m_dropCooldown <= 0.0f) {
        CreateBall({ m_cursorX, 7.0f, 0.0f }, m_nextLevel);
        m_dropCooldown = 0.5f;

        // 다음 레벨 결정 (1~4단계 가중치: 4,3,2,1)
        static std::mt19937 rng(std::random_device{}());
        static std::discrete_distribution<int> dist({4, 3, 2, 1});
        m_nextLevel = dist(rng);

        // 커서 메쉬/색상 즉시 갱신
        if (m_scene.GetRegistry().has<MeshRenderer>(m_cursorEntity)) {
            MeshRenderer& cr = m_scene.GetRegistry().get<MeshRenderer>(m_cursorEntity);
            cr.mesh = &m_ballMeshes[m_nextLevel];
            cr.material.tint = kBallLevels[m_nextLevel].tint;
        }
    }

    m_world.update(dt);
}

void SuikaApp::OnFixedUpdate() {
    m_world.fixed_update(1.0f / 60.0f);
}

void SuikaApp::OnRender() {
}

Entity SuikaApp::CreateWall(const Vec3& position, const Vec3& halfExtents) {
    Entity entity = m_scene.CreateEntity();

    Transform transform;
    transform.localPos = position;
    transform.localScale = halfExtents;
    m_scene.GetRegistry().add<Transform>(entity, transform);

    MeshRenderer renderer;
    renderer.mesh = &m_boxMesh;
    renderer.visible = true;
    renderer.material.tint = { 0.6f, 0.5f, 0.3f };
    renderer.material.albedo = nullptr;
    renderer.material.normalMap = nullptr;
    m_scene.GetRegistry().add<MeshRenderer>(entity, renderer);

    Collider collider;
    collider.shape = ColliderShape::AABB;
    collider.center = { 0.0f, 0.0f, 0.0f };
    collider.halfExtents = halfExtents;
    collider.restitution = 0.4f;
    collider.friction = 0.08f;
    m_scene.GetRegistry().add<Collider>(entity, collider);

    return entity;
}

Entity SuikaApp::CreateBall(const Vec3& position, int levelIndex) {
    levelIndex = std::clamp(levelIndex, 0, kMaxBallLevel - 1);
    const BallLevel& level = kBallLevels[levelIndex];
    Entity entity = m_scene.CreateEntity();

    Transform transform;
    transform.localPos = position;
    m_scene.GetRegistry().add<Transform>(entity, transform);

    MeshRenderer renderer;
    renderer.mesh = &m_ballMeshes[levelIndex];
    renderer.visible = true;
    renderer.material.tint = level.tint;
    renderer.material.albedo = nullptr;
    renderer.material.normalMap = nullptr;
    m_scene.GetRegistry().add<MeshRenderer>(entity, renderer);

    RigidBody body;
    body.useGravity = true;
    body.mass = 1.0f;
    // 완벽한 수직 정렬로 공 위에 서있는 현상 방지 — 미세한 랜덤 수평 속도 부여
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<float> jitter(-0.15f, 0.15f);
    body.velocity = { jitter(rng), 0.0f, 0.0f };
    m_scene.GetRegistry().add<RigidBody>(entity, body);

    Collider collider;
    collider.shape = ColliderShape::Sphere;
    collider.radius = level.radius;
    collider.restitution = 0.55f;  // 말랑한 공 탄성
    collider.friction = 0.08f;    // 낮춰서 수평 속도 보존
    m_scene.GetRegistry().add<Collider>(entity, collider);

    m_scene.GetRegistry().add<BallComponent>(entity, BallComponent{levelIndex});

    return entity;
}
