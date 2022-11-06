/***********************************************************************\
*                    кафедра № 304 2 курс 3 семестр информатика			*
*-----------------------------------------------------------------------*
*	Project type : solution												*
*	Project name : LW4													*
*	File name    : main.cpp												*
*	Language     : c/c++												*
*	Programmers  : Плоцкий Б.А. Раужев Ю. М.							*
*	Created      :  27/10/22											*
*	Last revision:  04/11/22											*
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

// коды для взаимодействия пользователья с программой
enum class input_codes
{
	exit = -1,
	template_program,
	list_create,
	list_push,
	list_pop,
	list_insert,
	list_print,
	list_delete,
	clear_console,
	find_max
};

// строка с коммандами
const char* command_str =
"\nВведите номер комманды:\n\
\t1. Выйти из программы.\n\
\t2. Запустить пример готового алгоритма.\n\
\t3. Создать список.\n\
\t4. Добавить элемент в конец списка.\n\
\t5. Удалить элемент с конца списка.\n\
\t6. Вставить элемент в определенную позицию.\n\
\t7. Распечатать список.\n\
\t8. Удалить список.\n\
\t9. Очистить консоль.\n\
\t10.Найти элемент с максимальным значением.";

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

// функция ведения диалога с пользователем
template<typename T>
void dialog();

// пример работы с List
void example_program();

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
node<T>* node_create(
	T _data,		// информация для хранения в элементе
	node<T>* _next,	// указатель на следующий элемент
	node<T>* _prev	// указатель на предыдущий элемент
);

// удаление элемента списка
template<typename T>
void node_delete(
	node<T>*& _node	// ссылка на элемент
);

// возвращение значение элемента
template<typename T>
T node_get_data(node<T>* _node);

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
bool list_is_empty(
	list<T>* _list	// указатель на список
);

// существует ли список
template<typename T>
bool list_exists(
	list<T>* _list	// указатель на список
);

// функция инициализации list
template<typename T>
list<T>* list_create();

// функция добавления элемента в конец списка
template<typename T>
void list_push(
	list<T>* _list,	// указатель на список
	T data			// информация для хранения в элементе
);

// функция удаления элемента из конца списка
template<typename T>
void list_pop(
	list<T>* _list	// указатель на список
);

// удаление списка
template<typename T>
void list_delete(
	list<T>*& _list	// адресс списка
);

// печать списка
template<typename T>
void list_print(
	list<T>* _list,				// печатаемый список
	ostream& _out_stream = cout	// поток для печати
);

// поиск максимального значения
template<typename T>
node<T>* list_find_max_elem(
	list<T>* _list,	// указатель на список
	int& _pos		// позиция элемента в списке
);

// включение элемента в определенную позицию списка
template<typename T>
void list_insert(
	list<T>* _list,	// указатель на список
	int _pos,		// позиция вставки
	T _insert_data	// информация для вставки
);

// печать индекса максимального элемента и его значения
template<typename T>
void list_print_max_elem(
	list<T>* _list	// указатель на список
);

/****************************************************************
*                Г Л А В Н А Я   Ф У Н К Ц И Я                  *
****************************************************************/

int main()
{
	setlocale(LC_ALL, "ru");
	 
	// запуск диалога с пользователем
	dialog<double>();

	return 0;
}

/****************************************************************
*              Р Е А Л И З А Ц И Я   Ф У Н К Ц И Й              *
****************************************************************/

/****************************************************************
*        В С П О М О Г А Т Е Л Ь Н Ы Е   Ф У Н К Ц И И          *
****************************************************************/

// ввод и проверка значений
template<typename T>
T input_and_check(T _min, T _max,
	const char* welcome_str, const char* err_str)
{
	// размер массива
	T num;

	// вывод сообщения
	cout << welcome_str << "\n";
	cin >> num;

	// если было введено некорректное значение
	if (num > _max || num < _min) {
		// если была введена не цифра
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}

		// отчистка консоли
		//system("cls");
		cout << err_str << "\n";

		// рекурсивное обращение
		num = input_and_check(_min, _max, welcome_str, err_str);
	}
	return num;
}

// функция ведения диалога с пользователем
template<typename T>
void dialog()
{
	/* коды комманд
	exit				-1
	template_program	0
	list_create			1
	list_push			2
	list_pop			3
	list_insert			4
	list_print			5
	list_delete			6
	clear_console		7
	find_max			8
	*/

	// переменная содержащая коды действий
	input_codes in_code;

	// элемент для вставки
	T elem;

	//позиция вставки
	int pos_to_insert;

	// переменная списка
	list<T>* lst = NULL;

	// максимальный элемент
	node<T>* max_elem = NULL;

	do
	{
		// запрос у пользователя следующих действий
		in_code = input_codes(input_and_check(1, 10, command_str) - 2);

		// запуск соответствующих функций
		switch (in_code)
		{
		case input_codes::exit:
			INFO("Произведен выход");
			break;

		case input_codes::template_program:
			INFO("Запуск примера кода");
			example_program();
			break;

		case input_codes::list_create:
			if (!list_exists(lst))
				lst = list_create<T>();
			else
				INFO("DIALOG: Список уже существует");
			break;

		case input_codes::list_push:
			elem = input_and_check(MIN_VALUE, MAX_VALUE,
				"Введите элемент для вставки в конец");
			list_push(lst, elem);
			break;

		case input_codes::list_pop:
			list_pop(lst);
			break;

		case input_codes::list_insert:
			elem = input_and_check(MIN_VALUE, MAX_VALUE,
				"Введите элемент для вставки");

			pos_to_insert = input_and_check(MIN_VALUE_INSERT, MAX_VALUE_INSERT,
				"Введите позицию для вставки");

			// вставка элемента 
			list_insert(lst, pos_to_insert, elem);
			break;

		case input_codes::list_print:
			// печать списка
			list_print(lst);
			break;

		case input_codes::list_delete:
			// удаление списка
			list_delete(lst);
			break;

		case input_codes::clear_console:
			system("cls");
			break;
			 
		case input_codes::find_max:
			list_print_max_elem(lst);
			break;

		default:
			INFO("Неизвестный код")
			break;
		}

	} while (
		// пока пользователь не захотел выйти из программы
		// или пока не запустил пример программыЫ
		in_code != input_codes::exit &&
		in_code != input_codes::template_program
		);
}

// пример работы с List
void example_program()
{
	// создание списка
	list<double>* lst = list_create<double>();

	// добавление элементов в конец
	list_push(lst, 5.2);
	list_push(lst, 1.3);
	list_push(lst, 5.1456);
	list_push(lst, 45656.9);
	list_push(lst, 0.456);

	// вывод списка
	list_print(lst);

	// вставка элемента в определенную позицию
	list_insert(lst, 4, -10.0);
	list_insert(lst, 0, 800.5);
	list_insert(lst, 0, 99.009);

	// вывод списка
	list_print(lst);

	// удаление элементов списка с конца
	list_pop(lst);
	list_pop(lst);
	list_pop(lst);
	list_pop(lst);

	// вывод списка
	list_print(lst);

	// печать максимального элемента списка
	list_print_max_elem(lst);

	// удаление списка
	list_delete(lst);

	// вывод списка
	list_print(lst);
}

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

// возвращение значение элемента
template<typename T>
T node_get_data(node<T>* _node)
{
	// выход из функции, если элемент не существует
	if (_node == NULL)
	{
		INFO("NODE GET DATA: Элемент не существует");
		return 0;
	}

	return _node->m_data;
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
