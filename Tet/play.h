#pragma once
#include "game.h"
#include "eblocks.cpp"

using namespace std;

class Play
{
public:
	Play();
	~Play();
	void Draw();
	void HandleInput();
	
	void MoveBlockdown();
	
	bool gameOver;
	int score;
	Music music;

private:
	void MoveBlockLeft();
	void MoveBlockright();
	Block GetRandomBlock();
	vector<Block> GetAllBlocks();
	bool isBlockOutside();
	void RotateBlock();
	void Lockblock();
	bool BlockFits();
	void reset();
	void upScore(int linecl, int movepts);
	Grid grid;
	vector<Block> blocks;
	Block currentBlock;
	Block nextBlock;
	Sound rotatesound;
	Sound clearsound;


};

