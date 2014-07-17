
#include "service.h"
#include "stdafx.h"

NullSocket Service::nullNetwork = NullSocket();
Socket * Service::network = NULL;

Socket * Service::Network()
{
    if (network == NULL)
    {
        return &nullNetwork;
    }
    else
    {
        return network;
    }
}

void Service::Provide(Socket * service)
{
    if (network) { delete network; }
    network = service;
}

