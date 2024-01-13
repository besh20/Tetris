#include <iostream>
#include "game.h"
#include "colors.h"
using namespace std;

// 1. creating the grid 

Grid::Grid() {
	numRows = 20;
	numCols = 10;
	cellsize = 30;
	initialize();
	colors = GetCellcolors();
}
void Grid::initialize(){

	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			grid[row][column] = 0;
		}
	}

}

void Grid::print() {

	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			cout << grid[row][column] << " ";
		}
		cout << endl;
	}

}


void Grid::Draw() {
	
	for (int row = 0; row < numRows; row++)
	{
		for (int column = 0; column < numCols; column++)
		{
			int cellValue = grid[row][column] ;
			DrawRectangle(column * cellsize + 15, row * cellsize + 15, cellsize - 1, cellsize - 1, colors[cellValue]);
		}
		
	}

}

bool Grid::isCellOutside(int row, int column)
{
	if (row >= 0 && row < numRows && column >= 0 && column < numCols) {
		return false;
	}
	return true;

}

bool Grid::isCellEmpty(int row, int column)
{
	if (grid[row][column] == 0) {
		return true;
	}
	return false;
}

int Grid::clearfullrows()
{
	int completed = 0;
	for (int row = numRows-1; row >= 0; row--) {
		if (IsRowFull(row)) {
			clearRow(row);
			completed++;
		}
		else if (completed > 0) {
			moverowdown(row, completed);
		}
	}
	return completed;
}

bool Grid::IsRowFull(int row)
{
	for (int column = 0; column <numCols; column++)
	{
		if (grid[row][column] == 0) {
			return false;
		}
	}
	return true;
}

void Grid::clearRow(int row)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row][column] = 0;
		
	}
}

void Grid::moverowdown(int row, int numrows)
{
	for (int column = 0; column < numCols; column++)
	{
		grid[row + numrows ][column] = grid[row][column];
		grid[row][column] = 0;

	}
	
}



