#include "play.h"
#include <random>

Play::Play() {

	grid = Grid();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	gameOver = false;
	score = 0;
	InitAudioDevice();
	music = LoadMusicStream("Sounds/music.mp3");
	PlayMusicStream(music);
	rotatesound = LoadSound("Sounds/rotate.mp3");
	clearsound = LoadSound("Sounds/clear.mp3");


}

Play::~Play() {
	UnloadSound(rotatesound);
	UnloadSound(clearsound);
	UnloadMusicStream(music);
	CloseAudioDevice();
}

Block Play::GetRandomBlock() {
	if (blocks.empty()) {
		blocks = GetAllBlocks();
	}

	int randomIndex = rand() % blocks.size();
	Block block = blocks[randomIndex];
	blocks.erase(blocks.begin() + randomIndex);
		return block;
}

vector<Block> Play::GetAllBlocks() {

	return  { iblock(), jblock(), lblock(), oblock(), sblock(), tblock(),zblock()
	};
}

void Play::Draw() {

	grid.Draw();
	currentBlock.Draw(15,15);
	switch (nextBlock.id)
	{
		case 3:
			nextBlock.Draw(255, 290);
			break;
		case 4:
			nextBlock.Draw(255, 280);
			break;
		default:
			nextBlock.Draw(270, 270);
			break;
	}
	

}

void Play::HandleInput()
{
	int keyPressed = GetKeyPressed();
	if (gameOver && keyPressed != 0) {

		gameOver = false;
		reset();

	}
	switch (keyPressed) 
	{
	case KEY_LEFT:
		MoveBlockLeft();
		break;

	case KEY_RIGHT:
		MoveBlockright();
		break;

	case KEY_DOWN:
		MoveBlockdown();
		upScore(0, 1);
		break;

	case KEY_UP:
		RotateBlock();
		break;
	}

}

void Play::MoveBlockLeft() {
	if(!gameOver){
	currentBlock.Move(0, -1);

	if (isBlockOutside() || BlockFits() == false) {
		currentBlock.Move(0, 1);
	}
	}
}

void Play::MoveBlockright() {
	if (!gameOver) {
		currentBlock.Move(0, 1);

		if (isBlockOutside() || BlockFits() == false) {
			currentBlock.Move(0, -1);
		}
	}
}

void Play::MoveBlockdown() {
	if (!gameOver) {
		currentBlock.Move(1, 0);

		if (isBlockOutside() || BlockFits() == false) {
			currentBlock.Move(-1, 0);
			Lockblock();
		}
	}
}

bool Play::isBlockOutside()
{
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {
		if (grid.isCellOutside(item.row, item.column)) {
			return true;
		}
	}
	return false;
}

void Play::RotateBlock()
{
	if(!gameOver){
	currentBlock.Rotate();

		if(isBlockOutside() || BlockFits() == false) {
			currentBlock.undoRotate();
		}
		else
		{
			PlaySound(rotatesound);
		}
	}
}

void Play::Lockblock()
{
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {

		grid.grid[item.row][item.column] = currentBlock.id;
	}

	currentBlock = nextBlock;
	if (BlockFits() == false) {
		gameOver = true;
	}

	nextBlock = GetRandomBlock();
	int rowscl =  grid.clearfullrows();
	if (rowscl > 0) {
		PlaySound(clearsound);
			upScore(rowscl, 0);
	}
	


}

bool Play::BlockFits()
{
	vector<Position> tiles = currentBlock.GetCellPositions();
	for (Position item : tiles) {

		if (grid.isCellEmpty(item.row, item.column) == false) {
			return false;
		}
	}
	return true;
}

void Play::reset()
{
	grid.initialize();
	blocks = GetAllBlocks();
	currentBlock = GetRandomBlock();
	nextBlock = GetRandomBlock();
	score = 0;

}

void Play::upScore(int linecl, int movepts)
{
	switch (linecl) {

	case 1:
		score += 100;
		break;
	case 2:
		score += 300;
		break;
	case 3:
		score += 500;
		break;
	default:
		break;
	}
	score += movepts;
}




