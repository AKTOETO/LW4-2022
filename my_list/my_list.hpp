#pragma once
#include <iostream>

using namespace std;

// ���� ����� ������ �� ������� �������� (0, 1)
#define NEED_PRINT_DEBUG 0

// ����� � ������� ���������
#define INFO(str) if(NEED_PRINT_DEBUG) cout<<"\t"<<str<<"\n";

/****************************************************************
*							   N O D E					        *
****************************************************************/

// ������� ����������� ������
template<typename T>
class node
{
	T m_data;		// ����������
	node* m_next;	// ��������� �� ��������� �������
	node* m_prev;	// ��������� �� ���������� �������

public:

	// ����������� �� ���������
	node() :m_next(nullptr), m_prev(nullptr), m_data(T(0)) {};

	// ����������� � �������
	node(T _data, node<T>* _next, node<T>* _prev)
		:m_data(_data), m_next(_next), m_prev(_prev)
	{
		INFO("������� ��� ������");
	}

	// ����������
	~node()
	{
		m_next = nullptr;
		m_prev = nullptr;
		m_data = T(0);

		INFO("������� ��� ������");
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

// ������
template<typename T>
class my_list
{
	node<T>* m_begin;	// ��������� �� ������ �������
	node<T>* m_end;		// ��������� �� ������� ����� ����������
	int m_size;			// ���������� ��������� � ������

public:
	// �����������
	my_list() :m_begin(nullptr), m_end(nullptr), m_size(0) {};
	~my_list()
	{
		// �������, ���� ������ �� ����������
		//LIST_NOT_EXSISTS("DELETE");

		// ���� ������ �� ����
		while (!is_empty())
		{
			// ������� �������� ������ � �����
			pop();
		}

		INFO("������ ��� ������")
	}

	node<T>* get_begin() const { return m_begin; }
	node<T>* get_end() const { return m_end; }
	int get_size() const { return m_size; }

	// ���� �� ������
	bool is_empty() const { return m_begin == nullptr; }

	// ������� ���������� �������� � ����� ������
	void push(T data)
	{
		// ������� ����������
		node<T>* new_node;

		// ���� ������ ����
		if (is_empty())
		{
			// ������� ����� ������� ������ list
			new_node = new node<T>(data, nullptr, nullptr);

			// ���������� ������ ������ �������� � list
			// � �������� ������� ��������
			m_begin = new_node;
			m_end = new_node;
		}
		// ���� � ������ ���� ��������
		else
		{
			// ������� ������� ��� ������� � list
			new_node = new node<T>(data, nullptr, m_end);

			// ������������ ��������� ������� � list
			m_end->set_next(new_node);

			// ����������� ��� list
			m_end = new_node;
		}

		//����������� ���������� ���������
		m_size++;

		INFO("������� �������� � �����");
	}

	// ������� �������� �������� �� ����� ������
	void pop()
	{
		// �������, ���� ������ ����
		if (m_begin == nullptr)
		{
			return;
		}

		// ������� ��������
		node<T>* to_delete = m_end;

		// ���� � ������ ������� 2 ��������
		if (m_begin != to_delete)
		{
			// ��������� ������ list
			m_end = to_delete->get_prev();

			// ������ ������ � ��������� ��������
			to_delete->get_prev()->set_next(nullptr);
		}
		else
		{
			// �������� ������ ������, ����������
			// �� ������ � ��������� �������� ������
			m_begin = m_end = nullptr;
		}

		// �������� ������ ��������
		delete to_delete;

		// ���������� ������� ������ �� 1
		m_size--;

		INFO("��������� ������� ��� ������");
	}

	// ��������� �������� � ������������ ������� ������
	void insert(int _pos, T _insert_data)
	{
		// ������� ������ ���� ������ ������� ������
		if (_pos < 0 || _pos >= m_size)
		{
			cout << "\tINSERT: ������� " << _pos
				<<" � ������ �������� " <<m_size
				<<" �����������\n";
			return;
		}

		// ������� �������
		int cur_pos = 0;

		// ������� �������
		node<T>* cur_node = m_begin;

		// ���� �� ����� �� ������ �������
		while (cur_pos != _pos)
		{
			// ��������� ������ �� ������
			cur_node = cur_node->get_next();
			cur_pos++;
		}

		// �������� ������ �������� ������
		node<T>* instert_elem = 
			new node<T>(_insert_data, cur_node, cur_node->get_prev());

		// ��������� ������ � ��������� � ������
		// ���� ����� cur_node ���� ��������
		if (cur_node->get_prev() != nullptr)
		{
			cur_node->get_prev()->set_next(instert_elem);
		}
		// ����� ������ m_begin � ������ �� instert_elem
		else
		{
			m_begin = instert_elem;
		}
		cur_node->set_prev(instert_elem);

		// ���������� ������� ������
		m_size++;

		INFO("������� ��������");
	}

	// ������
	friend ostream& operator<<(ostream& _out_stream, const my_list<T>& _list)
	{
		// ������� ������� ��� ������ ������ �� list'�
		node<T>* cur_el = _list.get_begin();

		// ���� �� list'�, ���� �� ��������� �� �������� �������
		while (cur_el != nullptr)
		{
			// ����� ������ ��������
			_out_stream << cur_el->get_data() << '\n';

			// ������� � ���������� ��������
			cur_el = cur_el->get_next();
		}
		return _out_stream;
	}
};