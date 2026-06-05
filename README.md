# SuikaGame

`Cpp_Engine` 기반으로 제작한 3D 수박게임(Suika Game).

---

## 빌드 및 실행

```bash
cmake -S . -B build
cmake --build build
./build/bin/SuikaGame
```

> macOS OpenGL deprecation 경고는 무시해도 됩니다.

---

## 조작법

| 키 | 동작 |
|----|------|
| `←` / `→` | 드롭 위치 이동 |
| `Space` | 공 드롭 |

---

## 게임 규칙

- 위에서 공을 떨어뜨려 컨테이너 안에 쌓는다.
- **같은 레벨**의 공 2개가 충돌하면 한 단계 큰 공으로 합쳐진다.
- 합칠수록 점수가 올라간다.
- 공이 컨테이너 상단을 넘으면 **게임오버**.

---

## 공 레벨표

| 레벨 | 색상 | 반지름 | 점수 |
|------|------|--------|------|
| 1 | 빨강 | 0.3 | 1 |
| 2 | 주황 | 0.5 | 3 |
| 3 | 노랑 | 0.7 | 6 |
| 4 | 초록 | 0.9 | 10 |
| 5 | 파랑 | 1.1 | 15 |
| 6 | 보라 | 1.4 | 21 |
| 7 | 분홍 | 1.7 | 28 |
| 8 | 청록(수박) | 2.1 | 36 |

드롭되는 공은 **1~4단계 중 랜덤** (낮은 레벨일수록 높은 확률).  
커서가 다음에 떨어질 공의 실제 크기와 색상으로 표시된다.

---

## 프로젝트 구조

```
src/
├── app/
│   ├── SuikaApp.h/.cpp     # 게임 앱 메인 (컨테이너, 드롭, 커서)
│   ├── Application.h/.cpp  # 앱 기반 클래스
│   └── GameLoop.h/.cpp     # 게임 루프
├── game/
│   ├── BallDef.h           # 공 레벨 정의 (kBallLevels)
│   ├── BallComponent.h     # ECS 공 컴포넌트 (level, age)
│   ├── GameState.h         # 공유 상태 (score, gameOver)
│   ├── MergeSystem.h/.cpp  # 합체 시스템
│   └── GameOverSystem.h/.cpp # 게임오버 판정 시스템
├── systems/                # 엔진 시스템 (Physics, Collision, Render 등)
├── renderer/               # OpenGL 렌더러
├── ecs/                    # Entity-Component-System
└── ...
```

---

## 기반 엔진

[Cpp_Engine](../Cpp_Engine) — 직접 제작한 C++ 3D 엔진

- ECS (Entity-Component-System)
- Phong 셰이딩 OpenGL 렌더러
- AABB / Sphere 충돌 시스템
- 이벤트 버스 (EventBus)
- 고정 타임스텝 물리 (FixedUpdate 1/60초)
