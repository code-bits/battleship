
#pragma once

#define WM_SOCKET (WM_USER + 1)

class SocketListener
{
public:
    virtual void OnNetworkRead(const std::string & msg) = 0;
};


class Socket
{
public:
    Socket(HWND hWnd_);
    virtual ~Socket();

    virtual void HandleMessages(WPARAM, LPARAM);
    virtual void Read();
    virtual void Write();
    virtual void Send(std::string msg);

    void SetListener(SocketListener * l);

protected:
    Socket() { }
    HWND hWnd;
    bool canWrite;
    SOCKET connection;
    std::stringstream inputBuffer;
    SocketListener * listener;

};


class NullSocket : public Socket
{
public:
    NullSocket() { }
    virtual ~NullSocket() { }
    virtual void HandleMessages(WPARAM, LPARAM) { }
    virtual void Read() { }
    virtual void Write() { }
    virtual void Send(std::string msg) { }
private:

};


class Server : public Socket
{
public:
    Server(HWND w);
    virtual ~Server() {}
private:

};


class Client : public Socket
{
public:
    Client(HWND hWnd_);
    virtual ~Client() {}
private:

};

