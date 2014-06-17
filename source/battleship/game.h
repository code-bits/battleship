
#pragma once

#include "mouse.h"
#include "viewport_window.h"
#include <list>
#include <vector>


class Game
{
public:
    Game();
    virtual ~Game();
    virtual void Init();
    virtual void SceneInit();
    virtual void Run();

    virtual void GetInput(int message, WPARAM wParam, LPARAM lParam);
    virtual void Update();
    virtual void Render(double inFrame);

    virtual void OnLeftButtonDown();
    virtual void OnRightButtonDown();

private:
    ViewportWindow viewport;
    Mouse mouse;
    bool needUpdate;

    
};

