
#pragma once

#include "network.h"

class Service
{
public:
    static Socket* Network();
    static void Provide(Socket * service);
private:
    static Socket * network;
    static NullSocket nullNetwork;
};
