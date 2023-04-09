#include "game.h"
#include "Menu.h"


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int** field{};
	int choice{};

	do
	{
		system("cls");
		cout << "1. Играть\n" \
				"2. Настройки\n" \
				"3. Выход\n";
		cout << "Ввод: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
			field = GenField(global_field_row, global_field_col, global_bomb_count);
			Game(field);
			break;
		case 2:
			SettingsMenu();
			break;
		case 3:
			exit(0);
			break;
		default:
			cout << "Неверный ввод" << endl;
			system("pause");
			break;
		}
	} while (true);

	return 0;
}

