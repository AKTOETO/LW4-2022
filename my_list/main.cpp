// ТЕСТ my_list

#include <iostream>
#include "my_list.hpp"

int main()
{
	setlocale(LC_ALL, "ru");

	my_list<int> list;

	cout << list << endl;

	list.push(10);
	list.push(11);
	list.push(12);

	cout << list << endl;

	list.insert(3, 5);

	cout << list << endl;

	cout << list << endl;
}