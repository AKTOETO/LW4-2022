// ТЕСТ my_list

#include <iostream>
#include "my_list.hpp"

int main()
{
	setlocale(LC_ALL, "ru");

	my_list<int> list;

	list.push(10);
	list.push(11);
	list.push(12);

	cout << endl<< list;

	my_list<int> lst;

	lst.push(10);
	lst.push(11);
	lst.push(12);

	lst = list;
	cout << endl<< lst;

}