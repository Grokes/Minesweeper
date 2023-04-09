#include "game.h"
#include "Menu.h"

int global_field_row{ 9 };
int global_field_col{ 9 };
int global_bomb_count{ 10 };

void Game(int** field)
{
	Point step{};
	do
	{
		system("cls");
		PrintField(field);
		cout << "������� ���������� ����(x y): ";
		cin >> step.x;
		cin >> step.y;
		step.x -= 1;
		step.y = field[SIZE][ROW] - step.y;
		if (CheckStep(field, step) == 1)
			break;

	} while (true);
}

void SettingsMenu()
{
	int choice{};
	system("cls");
	cout << "������� ���������\n"
		"1. ˸����\n" \
		"2. �������\n" \
		"3. ������\n" \
		"����: ";
	cin >> choice;

	switch (choice)
	{
	case 1:
		global_field_col = 9;
		global_field_row = 9;
		global_bomb_count = 10;
		break;
	case 2:
		global_field_col = 16;
		global_field_row = 14;
		global_bomb_count = 40;
		break;
	case 3:
		global_field_col = 29;
		global_field_row = 14;
		global_bomb_count = 89;
		break;
	default:
		break;
	}
}