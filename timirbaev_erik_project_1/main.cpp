#include <iostream>

using namespace std;

struct Pipe
{
	string name;
	int length;
	double diameter;
	bool repair;
};

struct Station
{
	string name;
	int workshops;
	int workshops_in_operation;
	double effectiveness;
};

int get_length() {
	while (true)
	{
		int len;
		cin >> len;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the length of the pipe: ";
		}
		else
		{
			return len;
		}
	}
}

double get_diameter() {
	while (true)
	{
		double diam;
		cin >> diam;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the diameter of the pipe: ";
		}
		else
		{
			return diam;
		}
	}
}

bool repair() {
	while (true)
	{
		bool rep;
		cin >> rep;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Pipe under repair (0; 1): ";
		}
		else
		{
			return rep;
		}
	}
}

int workshops() {
	while (true)
	{
		int wshop;
		cin >> wshop;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Enter the number of the workshops: ";
		}
		else
		{
			return wshop;
		}
	}
}

int workshops_in_operation(int wshop) {
	while (true)
	{
		int wshop_in_op;
		cin >> wshop_in_op;
		if (!cin || wshop_in_op > wshop)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Workshops in operation: ";
		}
		else
		{
			return wshop_in_op;
		}
	}
}

double effectiveness() {
	while (true)
	{
		double eff;
		cin >> eff;
		if (!cin)
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Effectiveness: ";
		}
		else
		{
			return eff;
		}
	}
}

Pipe add_pipe() {
	Pipe p;
	cout << "Enter the name of the pipe: "; cin >> p.name;
	cout << "Enter the length of the pipe: "; p.length = get_length();
	cout << "Enter the diameter of the pipe: "; p.diameter = get_diameter();
	cout << "Pipe under repair (0; 1): "; p.repair = repair();
	return p;
}

Station add_station() {
	Station s;
	cout << "Enter the name of the compressor station: "; cin >> s.name;
	cout << "Enter the number of the workshops: "; s.workshops = workshops();
	cout << "Workshops in operation: "; s.workshops_in_operation = workshops_in_operation(s.workshops);
	cout << "Effectiveness: "; s.effectiveness = effectiveness();
	return s;
}

void data(Pipe p, Station s) {
	if (p.name.empty())
	{
		cout << "Please add a pipe." << endl;
	}
	else
	{
		cout << "Pipe name: " << p.name
			<< "\nPipe length: " << p.length
			<< "\nPipe diameter: " << p.diameter
			<< "\nRepair: " << p.repair << endl;
	}
	if (s.name.empty())
	{
		cout << "Please add a compressor station." << endl;
	}
	else
	{
		cout << "Station name: " << s.name
			<< "\nWorkshops: " << s.workshops
			<< "\nWorkshops in operation: " << s.workshops_in_operation
			<< "\nEffectiveness: " << s.effectiveness << endl;
	}
}

void menu() {
	Pipe pipe;
	Station station;
	while (true)
	{
		cout << "MENU" << endl
			<< "1. Add a pipe" << endl
			<< "2. Add a compressor station" << endl
			<< "3. Viewing all objects" << endl
			<< "4. Edit a pipe" << endl
			<< "5. Edit a compressor station" << endl
			<< "6. Save all" << endl
			<< "7. Download" << endl
			<< "0. Exit" << endl
			<< "Please enter an integer from 0 to 7: ";
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
				pipe = add_pipe();
				break;
			case 2:
				station = add_station();
				break;
			case 3:
				data(pipe, station);
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