#pragma once
#include <string>
#include <fstream>

class Station
{
private:
	std::string name;
	std::string id;
	int workshops;
	int workshops_in_operation;
	int effectiveness;

public:
	static int MaxID;
	Station();
	std::string GetName() { return name; };
	int GetWorkshops() { return workshops; };
	int GetWorkshopsOperation() { return workshops_in_operation; };
	std::string GetId() { return id; };

	Station& add_station(Station& s);
	void edit_station(Station& s, int number);
	void station_data(const Station& s);

	friend std::ofstream& operator << (std::ofstream& fout, const Station& s);
	friend std::ifstream& operator >> (std::ifstream& fin, Station& s);
};