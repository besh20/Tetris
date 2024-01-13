#include <iostream>
#include <raylib.h>
#include "play.h"
#include "colors.h"
using namespace std;

double lastUpdatedTime = 0;
bool EventTriggered(double interval) {

    double currentTime = GetTime();
    if (currentTime - lastUpdatedTime >= interval) {
        lastUpdatedTime = currentTime;
        return true;
    }
    return false;
}

int main()
{
    InitWindow(500, 620, "TETRIS");
    SetTargetFPS(60);

    Font font = LoadFontEx("res/monogram.ttf", 64, 0, 0);
   
    Play play = Play();

    while (WindowShouldClose() == false){
        UpdateMusicStream(play.music);
        play.HandleInput();

        if (EventTriggered(.2)) {

            play.MoveBlockdown();
        }

        BeginDrawing();
        ClearBackground(DARKBLUE);
        DrawText("Score",{ 375}, 38, 22, WHITE);
        DrawTextEx(font ,"Next", { 370,180 }, 27, 5, WHITE);

        if (play.gameOver) {
            DrawTextEx(font, "GAME OVER", { 320,450 }, 38, 2, WHITE);
        }
                
        DrawRectangleRounded({ 320,85,170,60 }, .5, 6, SKYBLUE);

        char scoreText[10];
        sprintf_s(scoreText, "%d", play.score);
        Vector2 textSize = MeasureTextEx(font, scoreText, 38, 2);
        DrawTextEx(font, scoreText, { 320 + (170 - textSize.x) / 2, 90}, 38, 2, WHITE);

        DrawRectangleRounded({ 320,225,170,180 }, .3, 6, SKYBLUE);

        play.Draw();
       
        EndDrawing();
    
    }
   
    CloseWindow();
}


