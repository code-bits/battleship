
#pragma once

#define WM_SOCKET (WM_USER + 1)

class Socket
{
public:
    Socket(HWND hWnd_);
    virtual ~Socket();

    virtual void HandleMessages(WPARAM, LPARAM);
    virtual void Read() = 0;
    virtual void Write() = 0;

protected:
    Socket() { }
    HWND hWnd;

};

class NullSocket : public Socket
{
public:
    NullSocket() { }
    virtual ~NullSocket() { }
    virtual void HandleMessages(WPARAM, LPARAM) { }
    virtual void Read() { }
    virtual void Write() { }
private:

};

class Server : public Socket
{
public:
    Server(HWND w);
    virtual ~Server() {}

    virtual void Read() { }
    virtual void Write() { }
private:

};


class Client : public Socket
{
public:
    Client(HWND hWnd_);
    virtual ~Client() {}

    virtual void Read() { }
    virtual void Write() { }
private:

};

