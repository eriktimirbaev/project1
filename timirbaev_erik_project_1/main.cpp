#include <iostream>

using namespace std;

void menu() {
	while (true)
	{
		cout << "1. Add a pipe" << endl
			<< "2. Add a compressor station" << endl
			<< "3. Viewing all objects" << endl
			<< "4. Edit a pipe" << endl
			<< "5. Edit a compressor station" << endl
			<< "6. Save all" << endl
			<< "7. Download" << endl
			<< "0. Exit" << endl;
		int num;
		cin >> num;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Error! Enter an integer from 0 to 7." << endl;
		}
		else
		{
			switch (num)
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
				cout << "Error! Enter an integer from 0 to 7." << endl;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}