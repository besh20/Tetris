#pragma once
#include "position.h"
#include<map>
#include <vector>
#include "colors.h"

using namespace std;


class Block
{
public:
	Block();
	void Draw(int offsetX, int offsetY);
	void Move(int rows, int columns);
	vector<Position> GetCellPositions();
	void Rotate();
	void undoRotate();
	int id;
	map<int, vector<Position>> cells;


private:
	int cellsize;
	int rotationState;
	vector<Color> colors;
	int rowOffset;
	int columnOffset;

};


