#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/****************************************************************
*					   К О Н С Т А Н Т Ы						*
****************************************************************/

// если нужна печать по каждому действию (0, 1)
#define NEED_PRINT_DEBUG 1

// минимальное и максимальное значение ввода элементов
#define MAX_VALUE 1000.0
#define MIN_VALUE -1000.0

// минимальное и максимальное значение ввода элементов
#define MAX_VALUE_INSERT 100000
#define MIN_VALUE_INSERT 0

// вывод в консоль сообщения
#define INFO(str) if(NEED_PRINT_DEBUG) cout<<"\t"<<str<<"\n";

// не существует ли список
#define LIST_NOT_EXSISTS(f_name)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": Список не существует\n";\
		return;\
	}

// не существует ли список, возвращаем ret_obj
#define LIST_NOT_EXSISTS_RET(f_name, ret_obj)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": Список не существует\n";\
		return ret_obj;\
	}

// пуст ли список
#define LIST_EMPTY(f_name)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": Список пуст\n";\
		return;\
	}

// пуст ли список, возвращаем ret_obj
#define LIST_EMPTY_RET(f_name, ret_obj)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": Список пуст\n";\
		return ret_obj;\
	}

// заполнение len элементов элементом symb
#define OUT_W(symb, len) fixed << setfill(symb) << setw(len)

/****************************************************************
*              П Р О Т О Т И П Ы   Ф У Н К Ц И Й                *
****************************************************************/

/****************************************************************
*        В С П О М О Г А Т Е Л Ь Н Ы Е   Ф У Н К Ц И И          *
****************************************************************/

// ввод и проверка значений
template<typename T = int>
T input_and_check(
	T _min,
	T _max,
	const char* welcome_str,
	const char* err_str = "Было введено некорректное значение"
);

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
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev)
{
	// создаем первый элемент в списке
	node<T>* new_node = new node<T>;

	// настраиваем только что созданный элемент
	new_node->m_data = _data;
	new_node->m_next = _next;
	new_node->m_prev = _prev;

	INFO("Элемент был создан");

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

	// обнуление памяти
	delete _node;

	// обнуление адреса
	_node = NULL;

	INFO("Элемент был удален");
}

/****************************************************************
*							   L I S T					        *
****************************************************************/

namespace list
{

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

		INFO("Список был создан");

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

		INFO("Элемент добавлен в конец");
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

		// уменьшение размера списка на 1
		_list->m_size--;

		INFO("Последний элемент был удален");
	}

	// удаление списка
	template<typename T>
	void list_delete(list<T>*& _list)
	{
		// выходим, если список не существует
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

		INFO("Список был удален")
	}

	// печать списка
	template<typename T>
	void list_print(list<T>* _list, ostream& _out_stream)
	{
		// выходим, если список не существует или пуст
		LIST_NOT_EXSISTS("PRINT");
		LIST_EMPTY("PRINT");

		// создаем элемент для чтения данных из list'а
		node<T>* cur_el = _list->m_begin;

		// индекс элемента
		int i = 0;

		// печать шапки таблицы
		_out_stream << OUT_W('_', 22) << '\n';

		// дополнительная информация о списке list
		_out_stream << "|_размер:_" <<
			OUT_W('_', 9) << _list->m_size << "_|\n";
		_out_stream << "|_индекс_|_значение_|\n";

		// идем по list'у, пока на наткнемся на конечный элемент
		while (cur_el != NULL)
		{
			// вывод данных элемента
			_out_stream << "| " << OUT_W(' ', 6) << i
				<< " | " << setprecision(1)
				<< OUT_W(' ', 8) << node_get_data(cur_el)
				<< " |\n";

			// переход к следующему элементу
			cur_el = cur_el->m_next;
			i++;
		}
		// печать конца таблицы
		_out_stream << OUT_W('-', 22) << '\n';
	}

	// поиск максимального значения
	template<typename T>
	node<T>* list_find_max_elem(list<T>* _list, int& _pos)
	{
		// выходим, если список не существует или пуст
		LIST_NOT_EXSISTS_RET("FIND", NULL);
		LIST_EMPTY_RET("FIND", NULL);

		// элемент списка, который мы ищем
		node<T>* data = _list->m_begin;

		// берем элемент, с помощью которого
		// пройдемся по всему списку
		// он равен второму по счету элементу в списке
		node<T>* cur_node = _list->m_begin->m_next;

		// обнуление позиции элемента
		int _cur_pos = 0;

		// пока не дошли до конца списка
		while (cur_node != NULL)
		{
			// сравниваем с помощью _comp информацию в 
			// cur_node и в следующем элементе
			if (cur_node->m_data >= data->m_data)
			{
				data = cur_node;
				_pos = _cur_pos;
			}

			_cur_pos++;
			// переход к следующему элементу
			cur_node = cur_node->m_next;
		}

		// возвращение найденного элемента списка
		// или возвращение NULL
		return data;
	}

	// включение элемента в определенную позицию списка
	template<typename T>
	void list_insert(list<T>* _list, int _pos, T _insert_data)
	{
		// выход, если список не существует
		LIST_NOT_EXSISTS("INSERT");

		// позиция должна быть меньше размера списка
		if (_pos < 0 || _pos >= _list->m_size)
		{
			cout << "\tINSERT: Позиция некорректна\n";
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
		// если перед cur_node есть элементы
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

		INFO("Элемент вставлен");
	}

	template<typename T>
	void list_print_max_elem(list<T>* _list)
	{
		LIST_NOT_EXSISTS("PRINT MAX ELEM");
		LIST_EMPTY("PRINT MAX ELEM");

		// позиция в списке
		int pos = 0;

		// поиск максимального значения в списке
		node<T>* max_elem = list_find_max_elem(_list, pos);

		// печать позиции максимального элемента
		// и самого элемента
		cout << "Позиция max элемента: " << pos + 1 << endl;
		cout << "Значение максимального элемента: "
			<< node_get_data(max_elem) << endl;
	}

	/**************** End Of LW4.cpp File ***************/

}