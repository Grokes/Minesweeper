#include "game.h"

int** GenField(int row, int col, int bomb_count)
{
	// Проверки
	if (bomb_count > row * col)
		return nullptr;

	if (row <= 0 || col <= 0)
		return nullptr;

	// Выделение памяти (Создание поля)
	int** field = new int* [row + 1] {};
	field[SIZE] = new int[2] {row + 1, col};
	for (int i{ 1 }; i < field[SIZE][ROW]; i++)
	{
		field[i] = new int [col] {};
		// Инициализация поля
		for (int j{}; j < field[SIZE][COL]; j++)
		{
			field[i][j] = -2;
		}
	}
	// Расстановка бомб
	SetBomb(field, bomb_count);

	return field;
}

int GetBombArround(int** field, Point pos)
{
	if (field == nullptr)
		return -999;

	int bomb_count{};

	for (int i{}; i < number_of_steps; i++)
	{
		Point new_pos{ pos.x + steps[i].x, pos.y + steps[i].y };
		if (ValidStep(field, new_pos))
		{
			if (field[new_pos.y][new_pos.x] == -1)
				bomb_count++;
		}
	}

	return bomb_count;
}

inline bool ValidStep(int** field, Point pos)
{
	return (pos.x >= 0 && pos.x < field[SIZE][COL] && pos.y >= 1 && pos.y < field[SIZE][ROW]);
}

bool CheckStep(int** field, Point pos)
{
	// Проверки
	if (field == nullptr)
		return 0;

	if (ValidStep(field, pos) == false)
		return 0;
	// Ход
	if (field[pos.y][pos.x] == -1)
	{
		EndGame(field, "Вы проиграли");
		return 1;
	}
	else
		field[pos.y][pos.x] = GetBombArround(field, pos);
	// После хода
	if (field[pos.y][pos.x] == 0)
		OpenArround(field, pos);

	if (CheckWin(field))
	{
		EndGame(field, "Вы победили");
		return 1;
	}

	return 0;
}

void DelField(int** field)
{
	if (field == nullptr)
		return;

	for (int i{}; i < field[SIZE][ROW]; i++)
	{
		delete[] field[i];
	}
	delete[] field;
}

bool CheckWin(int** field)
{
	for (int i{1}; i < field[SIZE][ROW]; i++)
	{
		for (int j{}; j < field[SIZE][COL]; j++)
		{
			if (field[i][j] == -2)
				return false;
		}
	}

	return true;
}

void SetBomb(int** field, int bomb_count)
{
	while (bomb_count > 0)
	{
		Point bomb_pos{};
		bomb_pos.x = rand() % field[SIZE][COL];
		bomb_pos.y = rand() % (field[SIZE][ROW] - 1) + 1;

		if (field[bomb_pos.y][bomb_pos.x] != -1)
		{
			field[bomb_pos.y][bomb_pos.x] = -1;
			--bomb_count;
		}
	}
}

void OpenArround(int** field, Point pos)
{
	for (int i{}; i < number_of_steps; i++)
	{
		Point new_pos{ pos.x + steps[i].x, pos.y + steps[i].y };
		if (ValidStep(field, new_pos))
		{
			if (field[new_pos.y][new_pos.x] == -2)
			{
				field[new_pos.y][new_pos.x] = GetBombArround(field, new_pos);
				if (field[new_pos.y][new_pos.x] == 0)
					OpenArround(field, new_pos);
			}
		}
	}
}

void PrintField(int** field, bool end)
{
	if (field == nullptr)
		return;

	for (int i{ 1 }; i < field[SIZE][ROW]; i++)
	{
		for (int j{}; j < field[SIZE][COL]; j++)
		{
			if (field[i][j] == -2)
				cout << " * |";
			else if (field[i][j] == 0)
				cout << "   |";
			else if (field[i][j] == -1 && !end)
				cout << " * |";
			else if (field[i][j] == -1 && end)
				cout << " @ |";
			else
				cout << " " << field[i][j] << " |";
		}
		cout << " " << field[SIZE][ROW] - i << endl;
		for (int i{ 1 }; i < field[SIZE][COL] + 1; i++)
		{
			cout << "----";
		}
		cout << endl;
	}
	for (int i{ 1 }; i < field[SIZE][COL] + 1; i++)
	{	
		if (i < 10)
			cout << " " << i << "  ";
		else
			cout << i << "  ";
	}
		
	cout << endl;
}

void EndGame(int** field, const char* str)
{
	system("cls");
	PrintField(field, 1);
	cout << str << endl;
	DelField(field);
	system("pause");
}