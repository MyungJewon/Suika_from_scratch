#pragma once
#include "platform/IWindow.h"
#include <memory>

class GameLoop;

class Application {
public:
    Application(int width, int height, const char* title);
    virtual ~Application();

    void Run();
    void RequestQuit() { m_running = false; }
    bool IsRunning() const { return m_running; }

    IWindow& GetWindow() { return *m_window; }
    const IWindow& GetWindow() const { return *m_window; }

protected:
    virtual void OnInit() {}
    virtual void OnUpdate(float) {}
    virtual void OnFixedUpdate() {}
    virtual void OnRender();

private:
    friend class GameLoop;

    std::unique_ptr<IWindow> m_window;
    bool m_running = true;
};
  