#include <iostream>
#include <sstream>
unsigned short height;
double salary;
unsigned short ReadPersonAge();
std::string ReadPersonName();
void ReadPersonHeight();
void ReadPersonWeight(unsigned short&);
void ReadPersonSalary(double*);
void ReadPersonData(std::string&, unsigned short&, double&);
void ReadPersonData(std::string&, unsigned short&, unsigned short&, unsigned short&);
void WritePersonData(const std::string&, const unsigned short*, const std::string& height="", const std::string& weight ="");
#ifndef DO_NOT_DEFINE_MAIN
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
#endif
unsigned short ReadPersonAge() {
	unsigned short age;
	std::cout << "Введите возраст человека" << std::endl;
	std::cin >> age;
	return age;
}

std::string ReadPersonName() {
	std::string name;
	std::cout << "Введите имя человека" << std::endl;
	std::cin >> name;
	return name;
}

void ReadPersonHeight() {
	std::cout << "Введите рост человека" << std::endl;
	std::cin >> height;
}

void ReadPersonWeight(unsigned short &weight) {
	std::cout << "Введите вес человека" << std::endl;
	std::cin >> weight;
}
void ReadPersonSalary(double* salary) {
	std::cout << "Введите зарплату человека" << std::endl;
	std::cin >> *salary;
}
void ReadPersonData(std::string &name, unsigned short &age, double &salary) {
	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonSalary(&salary);
}
void ReadPersonData(std::string& name, unsigned short& age, unsigned short& height, unsigned short &weight) {
	name = ReadPersonName();
	age = ReadPersonAge();
	ReadPersonHeight();
	ReadPersonWeight(weight);
}
void WritePersonData(const std::string& name, const unsigned short* age, const std::string& height, const std::string& weight) {
	setlocale(LC_ALL, "Russian");
	std::cout << "Имя:\t" << name << std::endl 
		<< "Рост:\t" << height << std::endl 
		<< "Вес:\t" << weight << std::endl
		<< "Возраст:\t" << *age << std::endl 
		<< "Заработная плата:\t" << salary << std::endl;
}

