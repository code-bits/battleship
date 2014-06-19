#pragma once

class FieldClicker
{
public:
	FieldClicker(int top, int left, int size);
private:
	bool isInArea(int x, int y);
	int top;
	int	left;
	int	size;

};