#include "iostream"
#include "Header.h"
double salary;
void ReadPersonSalary(double* salary) {
	std::cout << "Введите зарплату человека" << std::endl;
	std::cin >> *salary;
}