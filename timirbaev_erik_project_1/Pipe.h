#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Pipe
{
private:
	std::string name;
	std::string id;
	int length;
	int diameter;
	bool repair;

public:
	static int MaxID;
	Pipe();
	Pipe(const Pipe& other);

	std::string GetName() { return name; };
	std::string GetId() { return id; };
	int GetLength() { return length; };
	int GetDiameter() { return diameter; };
	bool GetRepair() { return repair; };

	Pipe add_pipe(Pipe& p);
	void edit_pipe(Pipe& p, bool status);
	void pipe_data(const Pipe& p);

	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);

	~Pipe() {
		//std::cout << "~Pipe() " << this << std::endl;
	}
};

