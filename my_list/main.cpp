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
	cout << "\nsize: " << list.get_size();

	my_list<int> lst;

	lst.push(13);
	lst.push(14);
	lst.push(90);

	lst += list;
	cout << endl<< lst;
	cout << "\nsize: " << lst.get_size();

	cout<<"\n90: "<<lst.is_there_element(90);
	cout<<"\n1290: "<<lst.is_there_element(1290);

}