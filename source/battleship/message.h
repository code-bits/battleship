#pragma once

#include <string>
#include "cell.h"

class Message
{
public:
	Message(std::string , CellCoord );
    ~Message();
	static Message Decode(std::string );
	static std::string Encode(Message );
private:
	std::string action;
	CellCoord cellCoords;
};
