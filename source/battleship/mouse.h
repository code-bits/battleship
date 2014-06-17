#pragma once

#include <vector>

class IMouseListener
{
public:
    virtual void OnLeftMouseButtonDown(int x, int y) = 0;
    virtual void OnLeftMouseButtonUp(int x, int y) = 0;
    virtual void OnRightMouseButtonDown(int x, int y) = 0;
    virtual void OnRightMouseButtonUp(int x, int y) = 0;
    virtual void OnMouseMove(int x, int y) = 0;
};


class Mouse
{
public:
    Mouse() : x(0), y(0), dx(0), dy(0) { }

    void Update(int x_, int y_);
    int X() { return x; }
    int Y() { return y; }
    int DX() { return dx; }
    int DY() { return dy; }

    void LeftButtonDown();
    void LeftButtonUp();
    void RightButtonDown();
    void RightButtonUp();
    void Move();

    void RegisterListener(IMouseListener* listener);

private:
    int x;
    int y;
    int dx;
    int dy;
    std::vector<IMouseListener*> listeners;
};