#include "Station.h"
#include "Utilities.h"

using namespace std;

int Station::MaxID = 0;

Station::Station() {
	id = "Station" + to_string(++MaxID);
}

Station& Station::add_station(Station& s) {
	string wsh, wshio, eff;
	while (true) {
		cout << "Enter the name of the compressor station: "; getline(cin, s.name);
		if (s.name.empty()) cout << "Error!" << endl;
		else LOG(s.name) break;
	}
	cout << "Enter the number of the workshops: ";
	s.workshops = get_correct_number(0, 1000);
	cout << "Workshops in operation: ";
	s.workshops_in_operation = get_correct_number(0, s.workshops);
	cout << "Effectiveness: ";
	s.effectiveness = get_correct_number(0, 100);
	return s;
}

void Station::edit_station(Station& s, int number) {
	if (number <= s.workshops) s.workshops_in_operation = number;
}

void Station::station_data(const Station& s) {
	cout << "Station name: " << s.name
		<< "\nId: " << s.id
		<< "\nWorkshops: " << s.workshops
		<< "\nWorkshops in operation: " << s.workshops_in_operation
		<< "\nEffectiveness: " << s.effectiveness << endl;
}

ofstream& operator << (ofstream& fout, const Station& s) {
	if (fout.is_open()) {
		fout << s.name << endl;
		fout << s.id << endl;
		fout << s.workshops << endl;
		fout << s.workshops_in_operation << endl;
		fout << s.effectiveness << endl;
	}
	return fout;
}

ifstream& operator >> (ifstream& fin, Station& s) {
	if (fin.is_open()) {
		fin >> ws;
		getline(fin, s.name);
		fin >> s.id;
		fin >> s.workshops;
		fin >> s.workshops_in_operation;
		fin >> s.effectiveness;
		if (stoi(s.id.substr(7, s.id.size() - 7)) > Station::MaxID)
			Station::MaxID = stoi(s.id.substr(7, s.id.size() - 7));
	}
	return fin;
}