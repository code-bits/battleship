#include "iostream"
#include <string>
#include "../battleship/message.h"
#include <sstream>

int main()
{
	CellCoord cc;
	cc.col = 9;
	cc.row = 4;
	Message msg("check", cc);
	std::cout<<Message::Encode(msg)<<std::endl;


	system("pause");
	return 0;
}