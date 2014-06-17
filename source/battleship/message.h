#pragma once

class Message
{
private:
	std::string action;
	int row, column;
public:
	Message();
	~Message();
};
