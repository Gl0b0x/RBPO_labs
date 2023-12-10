#include "iostream"
#include "Header.h"
void WritePersonData(const std::string& name, const unsigned short* age, const std::string& height, const std::string& weight) {
	std::cout << "Имя:\t" << name << std::endl
		<< "Рост:\t" << height << std::endl
		<< "Вес:\t" << weight << std::endl
		<< "Возраст:\t" << *age << std::endl
		<< "Заработная плата:\t" << salary << std::endl;
}