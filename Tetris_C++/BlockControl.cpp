#include "BlockControl.h"
#include "block.h"
#include "map.h"

using namespace std;

BlockControl::BlockControl() 
{
	cur = { 0, 0 };
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	blockType = 0;
	blockAngle = 0;
	
}
bool BlockControl::isCollisionalToFloor()
{
	int x;

	for (x = 0; x < 4; ++x) {
		if (map[cur.Y + 3][cur.X + x * 2] && block[blockType][blockAngle][2][x * 2])
			return true;
		if (map[cur.Y + 4][cur.X + x * 2] != 0 && block[blockType][blockAngle][3][x * 2])
			return true;
	}
	return false;
}
bool BlockControl::isCollisionalToLeft()
{
	return false;
}
bool BlockControl::isCollisionalToRight()
{
	return false;
}
void BlockControl::spin()
{
	blockAngle++;
	blockAngle %= 4;
}
void BlockControl::backSpin()
{
	blockAngle += 3;
	blockAngle %= 4;
}
void BlockControl::drop()
{
	cout << "drop" << endl;
}
void BlockControl::down()
{
	if (isCollisionalToFloor()) 
		return;
	
	eraseBlock();
	cur.Y++;
	showBlock();
}
void BlockControl::moveLeft()
{
	if (isCollisionalToLeft())
		return;

	eraseBlock();
	cur.X -= 2;
	showBlock();
}
void BlockControl::moveRight()
{
	if (isCollisionalToRight())
		return;

	eraseBlock();
	cur.X += 2;
	showBlock();
}
void BlockControl::showMap()
{
	int x, y;

	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(handle, cur);

	for (y = 0; y < 21; ++y) {
		for (x = 0; x < 12; ++x)
			if (map[y][x * 2] == 9)
				cout << "��";
			else
				cout << "  ";
		cur.Y++;
		SetConsoleCursorPosition(handle, cur);
	}
}
void BlockControl::showBlock()
{
	int y, x;
	int empty = 0;

	SetConsoleCursorPosition(handle, cur);

	for (y = 0; y < 4; ++y) {
		for (x = 0; x < 4; ++x) {
			if (block[blockType][blockAngle][y][x] == 1)
				cout << "��";
			else {
				cur.X += 2;
				empty += 2;
				SetConsoleCursorPosition(handle, cur);
			}
		}
		cur.X -= empty;
		empty = 0;
		cur.Y++;
		SetConsoleCursorPosition(handle, cur);
	}
	cur.Y -= 4;
}
void BlockControl::setBlock()
{
	blockType = 3;//rand() / 7;
	blockAngle = 0;
	cur.X = 8;
	cur.Y = 0;
}
void BlockControl::eraseBlock()
{
	int i, j;

	SetConsoleCursorPosition(handle, cur);

	for (i = 0; i < 4; ++i) {
		for (j = 0; j < 4; ++j)
			cout << "  ";
		cur.Y++;
		SetConsoleCursorPosition(handle, cur);
	}
	cur.Y -= 4;
}
