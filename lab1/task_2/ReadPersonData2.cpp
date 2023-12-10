#include "iostream"
#include "Header.h"
void ReadPersonData(std::string& name, unsigned short& age, unsigned short& height, unsigned short& weight) {
	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonHeight();
	ReadPersonWeight(weight);
}