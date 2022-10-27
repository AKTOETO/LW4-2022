/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : LW4													*
*	File name    : main.cpp												*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  27/10/22											*
*	Last revision:  --/10/22											*
*	Comment(s)   : 														*
*																		*
*	/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : LW1													*
*	File name    : main.cpp												*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  12/09/22											*
*	Last revision:  25/09/22											*
*	Comment(s)   : 														*
*																		*
*	Реализовать заданный согласно варианту задания линейный список,		*
*	состоящий из 20 элементов заданного типа. Интерфейс должен 			*
*	включать для всех вариантов следующие операции:						*
*		- создание списка;												*
*		- вывод на экран и/или в файл значений элементов списка			*
*			с их индексами (номерами);									*
*		- удаление списка,												*
*	а также некоторые из дополнительных операций						*
*	(согласно варианту задания):										*
*		2.Поиск в списке элемента с максимальным значением с			*
*			получением его номера в списке (повторное вхождение			*
*			одного и того же значения может быть разрешено или			*
*			запрещено – см. вариант).									*
*		5.Включение нового элемента в позицию списка с заданным			*
*			в программе номером.										*
*		7.Удаление элемента из конца списка.							*
*																		*
\***********************************************************************/
#include <iostream>
#include <fstream>

// если нужна печать по каждому действию
//#define NEED_PRINT_DEBUG

using namespace std;

// элемент двусвязного списка
template<typename T>
struct node
{
	T m_data;		// информация
	node* m_next;	// указатель на следующий элемент
	node* m_prev;	// указатель на предыдущий элемент

	// конструктор
	node() :m_next(NULL), m_prev(NULL), m_data(T(0)) {};
};

// создание элемента списка
template<typename T>
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev)
{
	// создаем первый элемент в списке
	node<T>* new_node = new node<T>;

	// настраиваем только что созданный элемент
	new_node->m_data = _data;
	new_node->m_prev = _prev;
	new_node->m_next = _next;

#ifdef NEED_PRINT_DEBUG
	cout << "Node was created\n";
#endif // NEED_PRINT_DEBUG
	return new_node;
}

// удаление элемента списка
template<typename T>
void node_delete(node<T>* _node)
{
	// разрыв связей с другими элементами
	_node->m_data = T(0);
	_node->m_next = NULL;
	_node->m_prev = NULL;

	// удаление элемента списка
	delete _node;

	// обнуление памяти
	_node = NULL;

#ifdef NEED_PRINT_DEBUG
	cout << "Node was deleted\n";
#endif // NEED_PRINT_DEBUG
}

// печать элемента списка
template<typename T>
void node_print(node<T>* _node, ostream& _out_stream = cout)
{
	// выход из функции, если элемент не существует
	if (_node == NULL)
	{
#ifdef NEED_PRINT_DEBUG
		cout<<  "Node does not exist\n";
#endif // NEED_PRINT_DEBUG
		return;
	}

	// печать данных в поток
	_out_stream << _node->m_data;
}

// список
template<typename T>
struct list
{
	node<T>* m_begin;	// указатель на первый элемент
	node<T>* m_end;		// указатель на элемент после последнего
	int m_size;			// количество элементов в списке

	// конструктор
	list() :m_begin(NULL), m_end(NULL), m_size(0) {};
};

// функция инициализации list
template<typename T>
list<T>* list_create()
{
	// выделение памяти под список
	list<T>* _list = new list<T>;

	// создание элемента после конца списка
	node<T>* new_node = new node<T>;
	_list->m_end = new_node;

#ifdef NEED_PRINT_DEBUG

	cout << "List was created\n";

#endif // NEED_PRINT_DEBUG

	// возвращение адресса списка list
	return _list;
}

// функция добавления элемента в конец списка
template<typename T>
void list_push(list<T>* _list, T data)
{
	// если список пуст
	if (_list->m_end->m_prev == NULL)
	{
		// создаем новый элемент списка list
		node<T>* new_node = node_create<T>(data, _list->m_end, NULL);

		// записываем адресс нового элемента в list
		// в качестве первого элемента
		_list->m_begin = new_node;
		_list->m_end->m_prev = new_node;
	}
	// если в списке есть элементы
	else
	{
		// создаем элемент для вставки в list
		node<T>* new_node = node_create<T>(
			data, _list->m_end, _list->m_end->m_prev);

		// настравиваем последний элемент в list
		_list->m_end->m_prev->m_next = new_node;

		// настраиваем сам list
		_list->m_end->m_prev = new_node;
	}

	//увеличиваем количество элементов
	_list->m_size++;
}

// удаление списка
template<typename T>
void list_delete(list<T>*& _list)
{
	if (_list->m_begin != _list->m_end)
	{
		// создаем элемент для чтений данных из list'а
		node<T>* cur_el = _list->m_begin;

		// проходимся по всему списку
		while (cur_el != _list->m_end)
		{
			// переход к следующему элементу
			cur_el = cur_el->m_next;

			// удаление предыдущего элемента списка
			node_delete(cur_el->m_prev);
		}
		// разрыв связи элементе после последнего в list
		// удаление временного элемента
		cur_el->m_prev = NULL;
		delete cur_el;

		// разрыв связей в list
		_list->m_begin = NULL;
		_list->m_end = NULL;

		// удаление дополнительной информации
		_list->m_size = 0;
	}

	// удаление самого списка
	delete _list;

	// обнуление памяти
	_list = NULL;

#ifdef NEED_PRINT_DEBUG

	cout << "List was deleted\n";
#endif // NEED_PRINT_DEBUG
}

// печать списка
template<typename T>
void list_print(list<T>* _list, ostream& _out_stream = cout)
{
	// выход из функции, если список не существует
	if (_list == NULL)
	{

#ifdef NEED_PRINT_DEBUG
		cout << "List does not exist\n";
#endif // NEED_PRINT_DEBUG

		return;
	}
	
	// дополнительная информация о списке list
	_out_stream << "size: " << _list->m_size << endl;

	// создаем элемент для чтений данных из list'а
	node<T>* cur_el = _list->m_begin;

	// идем по list'у, пока на наткнемся на конечный элемент
	int i = 0;
	while (cur_el != _list->m_end)
	{
		// вывод данных элемента
		_out_stream << "index: " << i << " data: ";
		node_print(cur_el, _out_stream);
		_out_stream << endl;

		// переход к следующему элементу
		cur_el = cur_el->m_next;
		i++;
	}	
}

int main()
{
	// для тестов 
	ofstream fout("out.txt");

	list<int>* lst = list_create<int>();

	list_push(lst, 1);
	list_push(lst, 2);
	list_push(lst, 3);

	list_print(lst);

	list_delete(lst);

}

/**************** End Of LW4.cpp File ***************/
