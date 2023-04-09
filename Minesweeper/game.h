#pragma once
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define DEBUG -99
#define SIZE 0
#define ROW 0
#define COL 1

struct Point
{
	int x;
	int y;
};

const int number_of_steps = 8;
const Point steps[number_of_steps] = {  {-1, -1},
										{0, -1}, 
										{1, -1},
										{-1, 0},
										{1, 0},
										{-1, 1},
										{0, 1},
										{1, 1},
													};

using namespace std;

int** GenField(int row, int col, int bomb_count);
void PrintField(int** arr, bool end = 0);
int GetBombArround(int** field, Point pos);
inline bool ValidStep(int** field, Point pos);
bool CheckStep(int** field, Point pos);
bool CheckWin(int** field);
void DelField(int** field);
void SetBomb(int** field, int bomb_count);
void EndGame(int** field, const char* str);
void OpenArround(int** field, Point pos);
