
#include "network.h"
#include "stdafx.h"


Socket::Socket(HWND hWnd_)
{
    hWnd = hWnd_;
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
}


Socket::~Socket()
{
    WSACleanup();
}


void Socket::HandleMessages(WPARAM wParam, LPARAM lParam)
{
    if (WSAGETSELECTERROR(lParam))
    {
        // Display the error and close the socket
        std::cout << WSAGetLastError() << std::endl;
        closesocket(wParam);
        return;
    }
    // Determine what event occurred on the
    // socket
    switch(WSAGETSELECTEVENT(lParam))
    {
    case FD_ACCEPT:
        {
            // Accept an incoming connection
            SOCKET Accept = accept(wParam, NULL, NULL);
            // Prepare accepted socket for read,
            // write, and close notification
            WSAAsyncSelect(Accept, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);
            std::cout << "Connection accepted\n";
        }
        break;

    case FD_CONNECT:
        std::cout << "Connected!\n";
        break;

    case FD_READ:
        {
            // Receive data from the socket in
            // wParam
            char buffer[255] = "";
            recv(wParam, buffer, 255, 0);
            std::cout << buffer;
        }
        break;
    case FD_WRITE:
        std::cout << "Ready to write to socket.\n";
        send(wParam, "hey\n", 4, 0);
        break;

    case FD_CLOSE:
        // The connection is now closed
        std::cout << "Connection closed\n";
        closesocket(wParam);
        break;
    }
}


Server::Server(HWND hWnd_) : Socket(hWnd_)
{
    SOCKET Listen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    // Bind the socket to port 5150
    // and begin listening for connections
    SOCKADDR_IN InternetAddr;
    InternetAddr.sin_family = AF_INET;
    InternetAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    InternetAddr.sin_port = htons(5150);
    bind(Listen, (PSOCKADDR) & InternetAddr, sizeof(InternetAddr));
    // Set up window message notification on
    // the new socket using the WM_SOCKET define
    // above
    WSAAsyncSelect(Listen, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);
    listen(Listen, 5);
}


Client::Client(HWND hWnd_) : Socket(hWnd_)
{
    SOCKET s = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    WSAAsyncSelect(s, hWnd, WM_SOCKET, FD_CONNECT|FD_CLOSE|FD_READ|FD_WRITE);


    struct hostent *host;
    host=gethostbyname("localhost");

    // Set up our socket address structure
    SOCKADDR_IN SockAddr;
    SockAddr.sin_port=htons(5150);
    SockAddr.sin_family=AF_INET;
    SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

    connect(s,(LPSOCKADDR)(&SockAddr),sizeof(SockAddr));
}


