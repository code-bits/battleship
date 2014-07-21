
#pragma once

#include "network.h"
#include <list>
#include <vector>

class FrameWindow;
class ViewportWindow;
class Player;
class BotPlayer;
class RemotePlayer;
class Game;


class Application : public SocketListener
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

    virtual void OnNetworkRead(const std::string & msg);

private:
    FrameWindow * frame;
    ViewportWindow * viewport;
    Mouse mouse;

    Player * mainPlayer;
    RemotePlayer * adversaryPlayer;
    Game * game;
};

