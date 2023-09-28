#include <iostream>
#include <fstream>

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

void bufer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int get_length() {
	while (true)
	{
		bufer();
		int len;
		cin >> len;
		if (!cin)
		{
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
		bufer();
		double diam;
		cin >> diam;
		if (!cin)
		{
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
		bufer();
		bool rep;
		cin >> rep;
		if (!cin)
		{
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
		bufer();
		int wshop;
		cin >> wshop;
		if (!cin)
		{
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
		bufer();
		int wshop_in_op;
		cin >> wshop_in_op;
		if (!cin || wshop_in_op > wshop)
		{
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
		bufer();
		double eff;
		cin >> eff;
		if (!cin)
		{
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

void edit_pipe(Pipe& p) {
	if (p.name.empty())
	{
		cout << "Please add a pipe." << endl;
	}
	else
	{
		cout << "Pipe under repair (0; 1): "; p.repair = repair();
	}
}

void edit_station(Station& s) {
	if (s.name.empty())
	{
		cout << "Please add a compressor station." << endl;
	}
	else
	{
		cout << "Workshops in operation: "; s.workshops_in_operation = workshops_in_operation(s.workshops);
	}
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

void to_file(Pipe p, Station s) {
	if (p.name.empty() || s.name.empty())
	{
		cout << "Please add a pipe and a station." << endl;
	}
	else
	{
		ofstream file;
		file.open("data.txt");
		if (file.is_open())
		{
			file << "Pipe name: " << p.name
				<< "\nPipe length: " << p.length
				<< "\nPipe diameter: " << p.diameter
				<< "\nRepair: " << p.repair
				<< "\nStation name: " << s.name
				<< "\nWorkshops: " << s.workshops
				<< "\nWorkshops in operation: " << s.workshops_in_operation
				<< "\nEffectiveness: " << s.effectiveness << endl;
		}
		file.close();
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
				edit_pipe(pipe);
				break;
			case 5:
				edit_station(station);
				break;
			case 6:
				to_file(pipe, station);
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
		bufer();
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	menu();
	return 0;
}