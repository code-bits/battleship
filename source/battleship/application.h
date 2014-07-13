
#pragma once

#include "mouse.h"
#include "player.h"
#include <list>
#include <vector>

class FrameWindow;
class ViewportWindow;

class Field;

class Application
{
public:
    Application();
    virtual ~Application();
    virtual void Init();
    virtual void SceneInit();
    virtual void Run();

    virtual void GetInput(HWND hWnd, int message, WPARAM wParam, LPARAM lParam);
    virtual void Update();
    virtual void Render(double inFrame);

    virtual void OnLeftButtonDown();
    virtual void OnRightButtonDown();

private:
    FrameWindow * frame;
    ViewportWindow * viewport;
    Mouse mouse;

    LocalPlayer * firstPlayer;
    Player * secondPlayer;
    Field * field;
};

