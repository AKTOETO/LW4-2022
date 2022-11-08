#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

/****************************************************************
*					   � � � � � � � � �						*
****************************************************************/

// ���� ����� ������ �� ������� �������� (0, 1)
#define NEED_PRINT_DEBUG 1

// ����������� � ������������ �������� ����� ���������
#define MAX_VALUE 1000.0
#define MIN_VALUE -1000.0

// ����������� � ������������ �������� ����� ���������
#define MAX_VALUE_INSERT 100000
#define MIN_VALUE_INSERT 0

// ����� � ������� ���������
#define INFO(str) if(NEED_PRINT_DEBUG) cout<<"\t"<<str<<"\n";

// �� ���������� �� ������
#define LIST_NOT_EXSISTS(f_name)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": ������ �� ����������\n";\
		return;\
	}

// �� ���������� �� ������, ���������� ret_obj
#define LIST_NOT_EXSISTS_RET(f_name, ret_obj)\
	if(!list_exists(_list)){\
		cout << "\t" << f_name << ": ������ �� ����������\n";\
		return ret_obj;\
	}

// ���� �� ������
#define LIST_EMPTY(f_name)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": ������ ����\n";\
		return;\
	}

// ���� �� ������, ���������� ret_obj
#define LIST_EMPTY_RET(f_name, ret_obj)\
	if(list_is_empty(_list)){\
		cout << "\t" << f_name << ": ������ ����\n";\
		return ret_obj;\
	}

// ���������� len ��������� ��������� symb
#define OUT_W(symb, len) fixed << setfill(symb) << setw(len)

/****************************************************************
*              � � � � � � � � �   � � � � � � �                *
****************************************************************/

/****************************************************************
*        � � � � � � � � � � � � � � �   � � � � � � �          *
****************************************************************/

// ���� � �������� ��������
template<typename T = int>
T input_and_check(
	T _min,
	T _max,
	const char* welcome_str,
	const char* err_str = "���� ������� ������������ ��������"
);

/****************************************************************
*							   N O D E					        *
****************************************************************/

// ������� ����������� ������
template<typename T>
struct node
{
	T m_data;		// ����������
	node* m_next;	// ��������� �� ��������� �������
	node* m_prev;	// ��������� �� ���������� �������

	// �����������
	node() :m_next(NULL), m_prev(NULL), m_data(T(0)) {};
};

// �������� �������� ������
template<typename T>
node<T>* node_create(T _data, node<T>* _next, node<T>* _prev)
{
	// ������� ������ ������� � ������
	node<T>* new_node = new node<T>;

	// ����������� ������ ��� ��������� �������
	new_node->m_data = _data;
	new_node->m_next = _next;
	new_node->m_prev = _prev;

	INFO("������� ��� ������");

	return new_node;
}

// �������� �������� ������
template<typename T>
void node_delete(node<T>*& _node)
{
	// ������ ������ � ������� ����������
	_node->m_data = T(0);
	_node->m_next = NULL;
	_node->m_prev = NULL;

	// ��������� ������
	delete _node;

	// ��������� ������
	_node = NULL;

	INFO("������� ��� ������");
}

/****************************************************************
*							   L I S T					        *
****************************************************************/

namespace list
{

	// ������
	template<typename T>
	struct list
	{
		node<T>* m_begin;	// ��������� �� ������ �������
		node<T>* m_end;		// ��������� �� ������� ����� ����������
		int m_size;			// ���������� ��������� � ������

		// �����������
		list() :m_begin(NULL), m_end(NULL), m_size(0) {};
	};

	// ���� �� ������
	template<typename T>
	bool list_is_empty(list<T>* _list)
	{
		return _list->m_begin == NULL;
	}

	// ���������� �� ������
	template<typename T>
	bool list_exists(list<T>* _list)
	{
		return _list != NULL;
	}

	// ������� ������������� list
	template<typename T>
	list<T>* list_create()
	{
		// ��������� ������ ��� ������
		list<T>* _list = new list<T>;

		INFO("������ ��� ������");

		// ����������� ������� ������ list
		return _list;
	}

	// ������� ���������� �������� � ����� ������
	template<typename T>
	void list_push(list<T>* _list, T data)
	{
		// �����, ���� ������ �� ����������
		LIST_NOT_EXSISTS("PUSH");

		// ������� ����������
		node<T>* new_node;

		// ���� ������ ����
		if (list_is_empty(_list))
		{
			// ������� ����� ������� ������ list
			new_node = node_create<T>(data, NULL, NULL);

			// ���������� ������ ������ �������� � list
			// � �������� ������� ��������
			_list->m_begin = new_node;
			_list->m_end = new_node;
		}
		// ���� � ������ ���� ��������
		else
		{
			// ������� ������� ��� ������� � list
			new_node = node_create<T>(
				data, NULL, _list->m_end);

			// ������������ ��������� ������� � list
			_list->m_end->m_next = new_node;

			// ����������� ��� list
			_list->m_end = new_node;
		}

		//����������� ���������� ���������
		_list->m_size++;

		INFO("������� �������� � �����");
	}

	// ������� �������� �������� �� ����� ������
	template<typename T>
	void list_pop(list<T>* _list)
	{
		// �������, ���� ������ �� ���������� ��� ����
		LIST_NOT_EXSISTS("POP");
		LIST_EMPTY("POP");

		// ������� ��������
		node<T>* to_delete = _list->m_end;

		// ���� � ������ ������� 2 ��������
		if (_list->m_begin != to_delete)
		{
			// ��������� ������ list
			_list->m_end = to_delete->m_prev;

			// ������ ������ � ��������� ��������
			to_delete->m_prev->m_next = NULL;
		}
		else
		{
			// �������� ������ ������, ����������
			// �� ������ � ��������� �������� ������
			_list->m_begin = _list->m_end = NULL;
		}

		// �������� ������ ��������
		node_delete(to_delete);

		// ���������� ������� ������ �� 1
		_list->m_size--;

		INFO("��������� ������� ��� ������");
	}

	// �������� ������
	template<typename T>
	void list_delete(list<T>*& _list)
	{
		// �������, ���� ������ �� ����������
		LIST_NOT_EXSISTS("DELETE");

		// ���� ������ �� ����
		while (!list_is_empty(_list))
		{
			// ������� �������� ������ � �����
			list_pop(_list);
		}

		// �������� ������
		delete _list;

		// ��������� ������
		_list = NULL;

		INFO("������ ��� ������")
	}

	// ������ ������
	template<typename T>
	void list_print(list<T>* _list, ostream& _out_stream)
	{
		// �������, ���� ������ �� ���������� ��� ����
		LIST_NOT_EXSISTS("PRINT");
		LIST_EMPTY("PRINT");

		// ������� ������� ��� ������ ������ �� list'�
		node<T>* cur_el = _list->m_begin;

		// ������ ��������
		int i = 0;

		// ������ ����� �������
		_out_stream << OUT_W('_', 22) << '\n';

		// �������������� ���������� � ������ list
		_out_stream << "|_������:_" <<
			OUT_W('_', 9) << _list->m_size << "_|\n";
		_out_stream << "|_������_|_��������_|\n";

		// ���� �� list'�, ���� �� ��������� �� �������� �������
		while (cur_el != NULL)
		{
			// ����� ������ ��������
			_out_stream << "| " << OUT_W(' ', 6) << i
				<< " | " << setprecision(1)
				<< OUT_W(' ', 8) << node_get_data(cur_el)
				<< " |\n";

			// ������� � ���������� ��������
			cur_el = cur_el->m_next;
			i++;
		}
		// ������ ����� �������
		_out_stream << OUT_W('-', 22) << '\n';
	}

	// ����� ������������� ��������
	template<typename T>
	node<T>* list_find_max_elem(list<T>* _list, int& _pos)
	{
		// �������, ���� ������ �� ���������� ��� ����
		LIST_NOT_EXSISTS_RET("FIND", NULL);
		LIST_EMPTY_RET("FIND", NULL);

		// ������� ������, ������� �� ����
		node<T>* data = _list->m_begin;

		// ����� �������, � ������� ��������
		// ��������� �� ����� ������
		// �� ����� ������� �� ����� �������� � ������
		node<T>* cur_node = _list->m_begin->m_next;

		// ��������� ������� ��������
		int _cur_pos = 0;

		// ���� �� ����� �� ����� ������
		while (cur_node != NULL)
		{
			// ���������� � ������� _comp ���������� � 
			// cur_node � � ��������� ��������
			if (cur_node->m_data >= data->m_data)
			{
				data = cur_node;
				_pos = _cur_pos;
			}

			_cur_pos++;
			// ������� � ���������� ��������
			cur_node = cur_node->m_next;
		}

		// ����������� ���������� �������� ������
		// ��� ����������� NULL
		return data;
	}

	// ��������� �������� � ������������ ������� ������
	template<typename T>
	void list_insert(list<T>* _list, int _pos, T _insert_data)
	{
		// �����, ���� ������ �� ����������
		LIST_NOT_EXSISTS("INSERT");

		// ������� ������ ���� ������ ������� ������
		if (_pos < 0 || _pos >= _list->m_size)
		{
			cout << "\tINSERT: ������� �����������\n";
			return;
		}

		// ������� �������
		int cur_pos = 0;

		// ������� �������
		node<T>* cur_node = _list->m_begin;

		// ���� �� ����� �� ������ �������
		while (cur_pos != _pos)
		{
			// ��������� ������ �� ������
			cur_node = cur_node->m_next;
			cur_pos++;
		}

		// �������� ������ �������� ������
		node<T>* instert_elem =
			node_create<T>(_insert_data, cur_node, cur_node->m_prev);

		// ��������� ������ � ��������� � ������
		// ���� ����� cur_node ���� ��������
		if (cur_node->m_prev != NULL)
		{
			cur_node->m_prev->m_next = instert_elem;
		}
		// ����� ������ m_begin � ������ �� instert_elem
		else
		{
			_list->m_begin = instert_elem;
		}
		cur_node->m_prev = instert_elem;

		// ���������� ������� ������
		_list->m_size++;

		INFO("������� ��������");
	}

	template<typename T>
	void list_print_max_elem(list<T>* _list)
	{
		LIST_NOT_EXSISTS("PRINT MAX ELEM");
		LIST_EMPTY("PRINT MAX ELEM");

		// ������� � ������
		int pos = 0;

		// ����� ������������� �������� � ������
		node<T>* max_elem = list_find_max_elem(_list, pos);

		// ������ ������� ������������� ��������
		// � ������ ��������
		cout << "������� max ��������: " << pos + 1 << endl;
		cout << "�������� ������������� ��������: "
			<< node_get_data(max_elem) << endl;
	}

	/**************** End Of LW4.cpp File ***************/

}