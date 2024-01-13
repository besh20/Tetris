#pragma once
#include <vector>
#include <raylib.h>
using namespace std;


class Grid
{
public:
	Grid();
	void initialize();
	void print();
	void Draw();
	bool isCellOutside(int row, int column);
	bool isCellEmpty(int row, int column);
	int clearfullrows();
	int grid[20][10];
	
private: 
	bool IsRowFull(int row);
	void clearRow(int row);
	void moverowdown(int row, int numrows);
	int numRows;
	int numCols;
	int cellsize;
	vector<Color> colors;



};

