#pragma once
#include <iostream>
#include <string>

#define LOG(log) std::cerr << log << std::endl;

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		:old_buf(src.rdbuf()), stream(src)
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

inline bool int_check(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		if (isdigit(input[i])) continue;
		else return false;
	}
	if (input.length() == 0) return false;
	return true;
}

inline int get_correct_number(int min, int max) {
	std::string num;
	while ((std::getline(std::cin, num)).fail() || int_check(num) == false || stoi(num) < min || stoi(num) > max) {
		LOG(num);
		std::cout << "Please enter an integer from " << min << " to " << max << ": ";
	}
	LOG(num);
	return stoi(num);
}