#include "sstream"
#include "Header.h"
#include <iostream>
int main() {
	setlocale(LC_ALL, "Russian");
	unsigned short weight = 0;
	unsigned short age = 0;
	std::string name;
	ReadPersonData(name, age, salary);
	WritePersonData(name, &age);
	ReadPersonData(name, age, height, weight);
	WritePersonData(name, &age, std::to_string(height), std::to_string(weight));
}