#pragma once

#include <string>
#include "cell.h"

class Message
{
public:
    Message(std::string , CellCoord );
    static Message Decode(std::string s);
    static std::string Encode(Message msg);

    std::string action;
    CellCoord cellCoords;

};
