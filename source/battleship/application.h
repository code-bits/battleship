
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

    virtual void GetInput(const MSG & msg);
    virtual void Update();
    virtual void Render(double inFrame);

    virtual void OnNetworkRead(const std::string & msg);

private:
    FrameWindow * frame;
    ViewportWindow * viewport;
    Mouse mouse;

    Player * mainPlayer;
    RemotePlayer * adversaryPlayer;
    Game * game;
    bool needUpdate;
};

