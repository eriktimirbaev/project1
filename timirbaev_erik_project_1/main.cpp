#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "1. Добавить трубу" << endl
		 <<	"2. Добавить КС" << endl
		 <<	"3. Просмотр всех объектов" << endl
		 <<	"4. Редактировать трубу" << endl
		 <<	"5. Редактировать КС" << endl
		 <<	"6. Сохранить" << endl
		 <<	"7. Загрузить" << endl
		 <<	"0. Выход" << endl;
	int menu;
	cin >> menu;
	switch (menu)
	{
	case 1:
		cout << "1";
		break;
	case 2:
		cout << "2";
		break;
	case 3:
		cout << "3";
		break;
	case 4:
		cout << "4";
		break;
	case 5:
		cout << "5";
		break;
	case 6:
		cout << "6";
		break;
	case 7:
		cout << "7";
		break;
	case 0:
		cout << "0";
		break;
	default:
		cout << "Ошибка!" << endl;
	}
	return 0;
}