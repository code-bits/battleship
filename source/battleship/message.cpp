#include "message.h"
#include "stdafx.h"

Message::Message(std::string s, CellCoord coords)
{
    action = s;
    cellCoords = coords;
}


Message Message::Decode(std::string s)
{
    std::stringstream ss;
    ss << s;
    std::string action;
    CellCoord cc;
    
    ss >> action;
    ss >> cc.row;
    ss >> cc.col;
    return Message(action, cc);
}

std::string Message::Encode(Message msg)
{
    std::string s;
    s  =  "";
    s += msg.action;
    s += " ";
    s += std::to_string(msg.cellCoords.row);
    s += " ";
    s += std::to_string(msg.cellCoords.col);
    return s;
}

