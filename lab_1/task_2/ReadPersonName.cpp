#include "iostream"
#include "Header.h"
std::string ReadPersonName() {
	std::string name;
	std::cout << "¬ведите им€ человека" << std::endl;
	std::cin >> name;
	return name;
}