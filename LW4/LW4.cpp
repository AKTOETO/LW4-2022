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
*																		*																		*
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

using namespace std;

/****************************************************************
*					   К О Н С Т А Н Т Ы						*
****************************************************************/

// если нужна печать по каждому действию
#define NEED_PRINT_DEBUG 0

// вывод в консоль сообщения
#define INFO(str) if(NEED_PRINT_DEBUG) cout<<"\t"<<str<<"\n";

// не существует ли список
#define LIST_NOT_EXSISTS(f_name)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": list not exists\n";\
		return;\
	}

// не существует ли список возвращаем ret_obj
#define LIST_NOT_EXSISTS_RET(f_name, ret_obj)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": list not exists\n";\
		return ret_obj;\
	}

// пуст ли список
#define LIST_EMPTY(f_name)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": list is empty\n";\
		return;\
	}

// пуст ли список возвращаем ret_obj
#define LIST_EMPTY_RET(f_name, ret_obj)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": list is empty\n";\
		return ret_obj;\
	}

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/
/****************************************************************
*							   N O D E					        *
****************************************************************/

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
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev);

// удаление элемента списка
template<typename T>
void node_delete(node<T>*& _node);

// печать элемента списка
template<typename T>
void node_print(node<T>* _node, ostream& _out_stream = cout);

/****************************************************************
*							   L I S T					        *
****************************************************************/

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

// пуст ли список
template<typename T>
bool list_is_empty(list<T>* _list);

// существует ли список
template<typename T>
bool list_exists(list<T>* _list);

// функция инициализации list
template<typename T>
list<T>* list_create();

// функция добавления элемента в конец списка
template<typename T>
void list_push(list<T>* _list, T data);

// функция удаления элемента из конца списка
template<typename T>
void list_pop(list<T>* _list);

// удаление списка
template<typename T>
void list_delete(list<T>*& _list);

// печать списка
template<typename T>
void list_print(list<T>* _list, ostream& _out_stream = cout);

// поиск максимального значения
template<typename T>
node<T>* list_find_max_elem(list<T>* _list);

// включение элемента в определенную позицию списка
template<typename T>
void list_insert(list<T>* _list, int _pos, T _insert_data);

/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	list<double>* lst = list_create<double>();

	list_push(lst, 5.2);
	list_push(lst, 1.3);
	list_push(lst, 5.1456);
	list_push(lst, 45656.9);
	list_push(lst, 0.456);

	list_print(lst);

	list_insert(lst, 4, -10.0);
	list_insert(lst, 0, 800.5);
	list_insert(lst, 0, 99.009);

	list_print(lst);

	list_pop(lst);
	list_pop(lst);
	list_pop(lst);
	list_pop(lst);

	list_print(lst);

	node_print( list_find_max_elem(lst));

	list_delete(lst);

	list_print(lst);

	return 0;
}

/****************************************************************
*              Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й              *
****************************************************************/
/****************************************************************
*							   N O D E					        *
****************************************************************/

// создание элемента списка
template<typename T>
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev)
{
	// создаем первый элемент в списке
	node<T>* new_node = new node<T>;

	// настраиваем только что созданный элемент
	new_node->m_data = _data;
	new_node->m_next = _next;
	new_node->m_prev = _prev;

	INFO("Node was created");

	return new_node;
}

// удаление элемента списка
template<typename T>
void node_delete(node<T>*& _node)
{
	// разрыв связей с другими элементами
	_node->m_data = T(0);
	_node->m_next = NULL;
	_node->m_prev = NULL;

	// удаление элемента списка
	delete _node;

	// обнуление памяти
	_node = NULL;

	INFO("Node was deleted");
}

// печать элемента списка
template<typename T>
void node_print(node<T>* _node, ostream& _out_stream)
{
	// выход из функции, если элемент не существует
	if (_node == NULL)
	{
		INFO("Node does not exist");
		return;
	}

	// печать данных в поток
	_out_stream << "data: " << _node->m_data << '\n';
}

/****************************************************************
*							   L I S T					        *
****************************************************************/

// пуст ли список
template<typename T>
bool list_is_empty(list<T>* _list)
{
	return _list->m_begin == NULL;
}

// существует ли список
template<typename T>
bool list_exists(list<T>* _list)
{
	return _list != NULL;
}

// функция инициализации list
template<typename T>
list<T>* list_create()
{
	// выделение памяти под список
	list<T>* _list = new list<T>;

	INFO("List was created");

	// возвращение адресса списка list
	return _list;
}

// функция добавления элемента в конец списка
template<typename T>
void list_push(list<T>* _list, T data)
{
	// выход, если список не существует
	LIST_NOT_EXSISTS("PUSH");

	// элемент добавления
	node<T>* new_node;

	// если список пуст
	if (list_is_empty(_list))
	{
		// создаем новый элемент списка list
		new_node = node_create<T>(data, NULL, NULL);

		// записываем адресс нового элемента в list
		// в качестве первого элемента
		_list->m_begin = new_node;
		_list->m_end = new_node;
	}
	// если в списке есть элементы
	else
	{
		// создаем элемент для вставки в list
		new_node = node_create<T>(
			data, NULL, _list->m_end);

		// настравиваем последний элемент в list
		_list->m_end->m_next = new_node;

		// настраиваем сам list
		_list->m_end = new_node;
	}

	//увеличиваем количество элементов
	_list->m_size++;
}

// функция удаления элемента из конца списка
template<typename T>
void list_pop(list<T>* _list)
{
	// выходим, если список не существует или пуст
	LIST_NOT_EXSISTS("POP");
	LIST_EMPTY("POP");

	// элемент удаления
	node<T>* to_delete = _list->m_end;

	// если в списке минимум 2 элемента
	if (_list->m_begin != to_delete)
	{
		// настройка списка list
		_list->m_end = to_delete->m_prev;

		// разрыв связей с элементом удаления
		to_delete->m_prev->m_next = NULL;
	}
	else
	{
		// обнуляем адреса списка, указвающие
		// на первый и последний элементы списка
		_list->m_begin = _list->m_end = NULL;
	}

	// удаления самого элемента
	node_delete(to_delete);

	INFO("Last element was deleted");

	// уменьшение размера списка на 1
	_list->m_size--;
}

// удаление списка
template<typename T>
void list_delete(list<T>*& _list)
{
	// выходим, если список не существует или пуст
	LIST_NOT_EXSISTS("DELETE");

	// пока список не пуст
	while (!list_is_empty(_list))
	{
		// удаляем элементы списка с конца
		list_pop(_list);
	}

	// очищение памяти
	delete _list;

	// обнуление адреса
	_list = NULL;

	INFO("List was deleted")
}

// печать списка
template<typename T>
void list_print(list<T>* _list, ostream& _out_stream)
{
	// выходим, если список не существует или пуст
	LIST_NOT_EXSISTS("PRINT");
	LIST_EMPTY("PRINT");

	// дополнительная информация о списке list
	_out_stream << "size: " << _list->m_size << endl;

	// создаем элемент для чтения данных из list'а
	node<T>* cur_el = _list->m_begin;

	// индекс элемента
	int i = 0;

	// идем по list'у, пока на наткнемся на конечный элемент
	while (cur_el != NULL)
	{
		// вывод данных элемента
		_out_stream << "index: " << i << " ";
		node_print(cur_el, _out_stream);

		// переход к следующему элементу
		cur_el = cur_el->m_next;
		i++;
	}
}

// поиск максимального значения
template<typename T>
node<T>* list_find_max_elem(list<T>* _list)
{
	// выходим, если список не существует или пуст
	LIST_NOT_EXSISTS_RET("FIND", NULL);
	LIST_EMPTY_RET("FIND", NULL);

	// элемент списка, который мы ищем
	node<T>* data = NULL;

	// Если элементов в списке больше одного
	if (_list->m_begin != _list->m_end)
	{
		// берем элемент, с помощью которого
		// пройдемся по всему списку
		node<T>* cur_node = _list->m_begin->m_next;

		data = _list->m_begin;

		// пока не дошли до конца списка
		while (cur_node != NULL)
		{
			// сравниваем с помощью _comp информацию в 
			// cur_node и в следующем элементе
			if (cur_node->m_data >= data->m_data)
			{
				data = cur_node;
			}

			// переход к следующему элементу
			cur_node = cur_node->m_next;
		}
	}

	// возвращение найденного элемента списка
	// или возвращение NULL
	return data;
}

// включение элемента в определенную позицию списка
template<typename T>
void list_insert(list<T>* _list, int _pos, T _insert_data)
{
	// позиция должна быть не больше размера списка
	if (_pos < 0 || _pos >= _list->m_size)
	{
		cout << "\tINSERT: pos is incorrect\n";
		return;
	}

	// текущая позиция
	int cur_pos = 0;

	// текущий элемент
	node<T>* cur_node = _list->m_begin;

	// пока не дошли до нужной позиции
	while (cur_pos != _pos)
	{
		// смещаемся вправо по списку
		cur_node = cur_node->m_next;
		cur_pos++;
	}

	// создание нового элемента списка
	node<T>* instert_elem =
		node_create<T>(_insert_data, cur_node, cur_node->m_prev);

	// настройка связей у элементов в списке
	// если элемент вставляется не на нулевую позицию
	if (cur_node->m_prev != NULL)
	{
		cur_node->m_prev->m_next = instert_elem;
	}
	// иначе меняем m_begin у списка на instert_elem
	else
	{
		_list->m_begin = instert_elem;
	}
	cur_node->m_prev = instert_elem;

	// увеличение размера списка
	_list->m_size++;

	INFO("Element insterted");
}

/**************** End Of LW4.cpp File ***************/
