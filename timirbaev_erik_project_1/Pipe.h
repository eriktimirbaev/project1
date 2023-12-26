#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

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
	int GetLength() const { return length; };
	int GetDiameter() { return diameter; };
	bool GetRepair() { return repair; };
	double GetCapacity() const;

	Pipe add_pipe(Pipe& p);
	Pipe add_pipe_with_diameter(Pipe& p, int diameter);
	void edit_pipe(Pipe& p, bool status);
	void pipe_data(const Pipe& p);

	friend std::ofstream& operator << (std::ofstream& fout, const Pipe& p);
	friend std::ifstream& operator >> (std::ifstream& fin, Pipe& p);

	~Pipe() {
		//std::cout << "~Pipe() " << this << std::endl;
	}
};

