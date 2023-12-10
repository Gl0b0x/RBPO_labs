#include "iostream"
#include "Header.h"
void ReadPersonData(std::string& name, unsigned short& age, double &salary) {
	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonSalary(&salary);
}