#include <iostream>

using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	cout << "1. �������� �����" << endl
		 <<	"2. �������� ��" << endl
		 <<	"3. �������� ���� ��������" << endl
		 <<	"4. ������������� �����" << endl
		 <<	"5. ������������� ��" << endl
		 <<	"6. ���������" << endl
		 <<	"7. ���������" << endl
		 <<	"0. �����" << endl;
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
		cout << "������!" << endl;
	}
	return 0;
}