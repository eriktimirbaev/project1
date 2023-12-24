#include "Pipe.h"
#include "Utilities.h"

using namespace std;

int Pipe::MaxID = 0;

Pipe::Pipe() {
	//cout << "Pipe() " << this << endl;
	id = "Pipe" + to_string(++MaxID);
}

Pipe::Pipe(const Pipe& other) {
	name = other.name;
	id = other.id;
	length = other.length;
	diameter = other.diameter;
	repair = other.repair;
	//cout << "Pipe(&) " << this << endl;
}

Pipe Pipe::add_pipe(Pipe& p) {
	while (true) {
		cout << "Enter the name of the pipe: "; getline(cin, p.name);
		if (p.name.empty()) cout << "Error!" << endl;
		else LOG(p.name) break;
	}
	cout << "Enter the length of the pipe (meters): ";
	p.length = get_correct_number(0, 1000);
	cout << "Enter the diameter of the pipe (millimeters): ";
	p.diameter = get_correct_number(0, 1000);
	cout << "Pipe under repair (0; 1): ";
	p.repair = get_correct_number(0, 1);
	return p;
}

void Pipe::edit_pipe(Pipe& p, bool status) {
	p.repair = status;
}

void Pipe::pipe_data(const Pipe& p) {
	cout << "Pipe name: " << p.name
		<< "\nId: " << p.id
		<< "\nPipe length: " << p.length
		<< "\nPipe diameter: " << p.diameter
		<< "\nRepair: " << p.repair << endl;

}

ofstream& operator << (ofstream& fout, const Pipe& p) {
	if (fout.is_open()) {
		fout << p.name << endl;
		fout << p.id << endl;
		fout << p.length << endl;
		fout << p.diameter << endl;
		fout << p.repair << endl;
	}
	return fout;
}

ifstream& operator >> (ifstream& fin, Pipe& p) {
	if (fin.is_open()) {
		fin >> ws;
		getline(fin, p.name);
		fin >> p.id;
		fin >> p.length;
		fin >> p.diameter;
		fin >> p.repair;
		if (stoi(p.id.substr(4, p.id.size() - 4)) > Pipe::MaxID)
			Pipe::MaxID = stoi(p.id.substr(4, p.id.size() - 4));
	}
	return fin;
}