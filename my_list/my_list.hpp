#pragma once
#include <iostream>

using namespace std;

/****************************************************************
*							   N O D E					        *
****************************************************************/

// элемент двусвязного списка
template<typename T>
class node
{
	T m_data;		// информация
	node* m_next;	// указатель на следующий элемент
	node* m_prev;	// указатель на предыдущий элемент

public:

	// конструктор по умолчанию
	node() :m_next(nullptr), m_prev(nullptr), m_data(T(0)) {};

	// конструктор с данными
	node(T _data, node<T>* _next, node<T>* _prev)
		:m_data(_data), m_next(_next), m_prev(_prev)
	{
	}

	// деструктор
	~node()
	{
		m_next = nullptr;
		m_prev = nullptr;
	}

	void set_next(node<T>* _node) { m_next = _node; }
	void set_prev(node<T>* _node) { m_prev = _node; }
	void set_data(T _data) { m_data = _data; }

	node<T>* get_next() const { return m_next; }
	node<T>* get_prev() const { return m_prev; }
	T get_data() const { return m_data; }
};


/****************************************************************
*							   L I S T					        *
****************************************************************/

// список
template<typename T>
class my_list
{
	node<T>* m_begin;	// указатель на первый элемент
	node<T>* m_end;		// указатель на элемент после последнего
	int m_size;			// количество элементов в списке

public:
	// конструктор
	my_list() :m_begin(nullptr), m_end(nullptr), m_size(0) {};
	~my_list()
	{
		// пока список не пуст
		while (!is_empty())
		{
			// удаляем элементы списка с конца
			pop();
		}
	}

	node<T>* get_begin() const { return m_begin; }
	node<T>* get_end() const { return m_end; }
	int get_size() const { return m_size; }

	// пуст ли список
	bool is_empty() const { return m_begin == nullptr; }

	// есть ли этот элемент в списке
	bool is_there_element(T _data) const
	{
		node<T>* nd = m_begin;
		while (nd)
		{
			if (nd->get_data() == _data) return true;
			nd = nd->get_next();
		}
		return false;
	}

	// Очистка списка
	void clear()
	{
		// пока список не пуст
		while (!is_empty())
		{
			// удаляем элементы с конца
			pop();
		}
	}

	// функция добавления элемента в конец списка
	void push(T data)
	{
		// элемент добавления
		node<T>* new_node;

		// если список пуст
		if (is_empty())
		{
			// создаем новый элемент списка list
			new_node = new node<T>(data, nullptr, nullptr);

			// записываем адресс нового элемента в list
			// в качестве первого элемента
			m_begin = new_node;
			m_end = new_node;
		}
		// если в списке есть элементы
		else
		{
			// создаем элемент для вставки в list
			new_node = new node<T>(data, nullptr, m_end);

			// настравиваем последний элемент в list
			m_end->set_next(new_node);

			// настраиваем сам list
			m_end = new_node;
		}

		//увеличиваем количество элементов
		m_size++;
	}

	// функция удаления элемента из конца списка
	void pop()
	{
		// выходим, если список пуст
		if (m_begin == nullptr)
		{
			return;
		}

		// элемент удаления
		node<T>* to_delete = m_end;

		// если в списке минимум 2 элемента
		if (m_begin != to_delete)
		{
			// настройка списка list
			m_end = to_delete->get_prev();

			// разрыв связей с элементом удаления
			to_delete->get_prev()->set_next(nullptr);
		}
		else
		{
			// обнуляем адреса списка, указвающие
			// на первый и последний элементы списка
			m_begin = m_end = nullptr;
		}

		// удаления самого элемента
		delete to_delete;

		// уменьшение размера списка на 1
		m_size--;
	}

	// включение элемента в определенную позицию списка
	void insert(int _pos, T _insert_data)
	{
		// позиция должна быть меньше размера списка
		if (_pos < 0 || _pos >= m_size)
		{
			cout << "\tINSERT: Позиция " << _pos
				<< " в списке размером " << m_size
				<< " некорректна\n";
			return;
		}

		// текущая позиция
		int cur_pos = 0;

		// текущий элемент
		node<T>* cur_node = m_begin;

		// пока не дошли до нужной позиции
		while (cur_pos != _pos)
		{
			// смещаемся вправо по списку
			cur_node = cur_node->get_next();
			cur_pos++;
		}

		// создание нового элемента списка
		node<T>* instert_elem =
			new node<T>(_insert_data, cur_node, cur_node->get_prev());

		// настройка связей у элементов в списке
		// если перед cur_node есть элементы
		if (cur_node->get_prev() != nullptr)
		{
			cur_node->get_prev()->set_next(instert_elem);
		}
		// иначе меняем m_begin у списка на instert_elem
		else
		{
			m_begin = instert_elem;
		}
		cur_node->set_prev(instert_elem);

		// увеличение размера списка
		m_size++;
	}
	
	// удаление элемента на позиции _node
	void delete_node(node<T>* _node)
	{
		// если существует предыдущий элемент и текущий
		if (_node && _node->get_prev())
		{
			_node->get_prev()->set_next(_node->get_next());
		}
		// иначе если его нет
		else if (_node)
		{
			_node->get_next()->set_prev(NULL);
			m_begin = _node->get_next();
		}

		// если существует следующий элемент и текущий
		if (_node && _node->get_next())
		{
			_node->get_next()->set_prev(_node->get_prev());
		}
		// иначе если его нет
		else if (_node)
		{
			_node->get_prev()->set_next(NULL);
			m_end = _node->get_prev();
		}

		delete _node;

		m_size--;
	}

	// удаление элемента на позиции _pos
	void delete_node(int _pos)
	{
		if (0 <= _pos && _pos < m_size)
		{
			// элемент для удаления
			node<T>* temp = m_begin;
			int index = 0;

			// поиск элемента удаления
			while (temp && index < _pos)
			{
				index++;
				temp = temp->get_next();
			}

			delete_node(temp);
		}
	}

	// выполнение какого-то действия для всего списка
	template<class FUNC = void(node<T>*)>
	void for_each(FUNC _func)
	{
		node<T>* temp = m_begin;
		while (temp)
		{
			_func(temp);
			temp = temp->get_next();
		}
	}

	// возвращение элемента по индексу
	node<T>* get_element_by_index(int _index)
	{
		int ind = 0;
		node<T>* temp = m_begin;
		while (temp)
		{
			if (ind++ == _index) return temp;
			temp = temp->get_next();
		}
		return temp;
	}

	// печать
	friend ostream& operator<<(ostream& _out_stream, const my_list<T>& _list)
	{
		// создаем элемент для чтения данных из list'а
		node<T>* cur_el = _list.get_begin();

		// идем по list'у, пока на наткнемся на конечный элемент
		while (cur_el != nullptr)
		{
			// вывод данных элемента
			_out_stream << cur_el->get_data() << '\n';

			// переход к следующему элементу
			cur_el = cur_el->get_next();
		}
		return _out_stream;
	}

	// оператор присваивания со сложением
	my_list<T>& operator+=(const my_list<T>& _obj)
	{
		// добавление элементов одного списка в другой
		node<T>* temp = _obj.m_begin;
		while (temp)
		{
			push(temp->get_data());
			temp = temp->get_next();
		}

		return *this;
	}

	// оператор присваивания
	my_list<T>& operator=(const my_list<T>& _obj)
	{
		// очиста списка
		clear();

		// копирование элементов
		node<T>* temp = _obj.m_begin;
		while (temp)
		{
			push(temp->get_data());
			temp = temp->get_next();
		}

		return *this;
	}
};