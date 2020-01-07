#ifndef _list_h
#define _list_h

template<typename T, int items = 32>
class List
{
	using Order = bool (*)(T*, T*);
	static constexpr auto Order_default = [](T *, T*){ return false;};
	struct Node {bool is_empty; T data; Node * previous; Node * next;};
	struct Result{bool result; T item;};

public:
	List(Order order = Order_default);
	~List();

	void order_set(Order order);

	int size();

	void add(const T & item);
	bool add_when_unique(const T & item);
	template<typename C> bool add_when(const C & condition, const T & item);

	T * peek_at(int index = 0);	
	template<typename C> T * peek_item_where(const C & condition);
	template<typename C> bool has_item_where(const C & condition);
	template<typename C> int count_items_where(const C & condition);

	T withdraw();
	template<typename C> Result withdraw_when(const C & condition);


protected:
	Node * _node_empty_get();

	bool _node_is_more_important_than(Node* resident, Node * candidate);
	bool _node_is_connected(Node * node);

	void _node_attach_before(Node * resident, Node * candidate);
	void _node_attach_after(Node * resident, Node * candidate);
	void _node_deattach(Node * node);

private:
	Order _order;
	Node _node[items];
	Node * _head;
};

//---------------------------------------------| sconst/Destr |---------------------------------------------//

template<typename T, int items>
List<T, items>::List(Order order)
:
_order(order),
_head(nullptr)
{
	for (int i = 0;i<items;i++)
	{
		_node[i].is_empty = true;
		_node[i].previous = nullptr;
		_node[i].next = nullptr;
	}
}

template<typename T, int items>
List<T, items>::~List()
{
}

template<typename T, int items>
void List<T, items>::order_set(Order order)
{
	_order = order;
}

template<typename T, int items>
int List<T, items>::size()
{
	if (_head != nullptr)
	{
		int count = 0;
		auto head = _head;

		while(head != nullptr)
		{
			count++;
			head = head->next;
		}

		return count;
	}
	else
	{
		return 0;
	}
}

//==============================================| ADD |=============================================//

//---------------------------------------------| add |---------------------------------------------//

template<typename T, int items>
void List<T, items>::add(const T & item)
{
	auto node = _node_empty_get(); // try to obtain empty node

	if (node != nullptr) // no space avaiable
	{
		node->is_empty = false;
		node->data = item;
		node->previous = nullptr;
		node->next = nullptr;

		if (_head != nullptr) // more than one item
		{
			auto resident = _head; // pointer to iterate from head throught all elements

			while(!_node_is_connected(node)) // while node remains unconnected
			{
				if (_node_is_more_important_than(resident, node)) // node is more important than resident
				{
					_node_attach_before(resident, node); // connect before resident
				}
				else
				{
					if (resident->next == nullptr) // resident is last item currently
					{
						_node_attach_after(resident, node); // connect after resident
					}
					else
					{
						resident = resident->next; // next resident
					}
				}
			}
		}
		else
		{
			_head = node; // head becomes new node
		}
	}
	else
	{
		// error, no space
	}
}

//---------------------------------------------| add when unique |---------------------------------------------//

template<typename T, int items>
bool List<T, items>::add_when_unique(const T & item)
{
	auto resident = _head;

	while(resident)
	{
		if (resident->data == item)
		{
			return false;
		}
		else
		{
			resident = resident->next;
		}
	}

	add(item);

	return true;
}

//---------------------------------------------| add when not |---------------------------------------------//

template<typename T, int items>
template<typename C>
bool List<T, items>::add_when(const C & condition, const T & item)
{
	auto resident = _head;
	bool flag = true;

	while(resident)
	{
		if (!condition(&resident->data)) flag = false;

		resident = resident->next;
	}

	if (flag) add(item);

	return true;
}

//---------------------------------------------| peak |---------------------------------------------//

template<typename T, int items>
T * List<T, items>::peek_at(int index)
{
	auto * head = _head;
	T * result = nullptr;

	for (int i = 0;i<index + 1;i++)
	{
		if (head != nullptr)
		{
			if (i == index)
			{
				result = &head->data;
			}
			else
			{
				head = head->next;
			}
		}
		else
		{
			break;
		}
	}

	return result;
}

template<typename T, int items>
template<typename C>
T * List<T, items>::peek_item_where(const C & condition)
{
	auto resident = _head;

	while(resident)
	{
		if (condition(&resident->data))
		{
			return &resident->data;
		}
		else
		{
			resident = resident->next;
		}
	}

	return nullptr;
}

template<typename T, int items>
template<typename C>
bool List<T, items>::has_item_where(const C & condition)
{
	auto resident = _head;

	while(resident)
	{
		if (condition(&resident->data))
		{
			return true;
		}
		else
		{
			resident = resident->next;
		}
	}

	return false;
}

template<typename T, int items>
template<typename C>
int List<T, items>::count_items_where(const C & condition)
{
	auto resident = _head;
	int count = 0;

	while(resident)
	{
		if (condition(&resident->data))
		{
			count++;
			resident = resident->next;
		}
		else
		{
			resident = resident->next;
		}
	}

	return count;
}

template<typename T, int items>
T List<T, items>::withdraw()
{
	if (_head != nullptr)
	{
		T item = _head->data;
		_node_deattach(_head);
		return item;
	}
	else
	{
		return {};
	}
}

template<typename T, int items>
template<typename C>
typename List<T, items>::Result List<T, items>::withdraw_when(const C & condition)
{
	auto resident = _head;

	while(resident)
	{
		if (condition(&resident->data))
		{
			auto temp = resident->data;
			_node_deattach(resident);
			return {true, temp};
		}
		else
		{
			resident = resident->next;
		}
	}
	return {false, {}};
}

//==============================================| helpers |=============================================//

template<typename T, int items>
typename List<T, items>::Node * List<T, items>::_node_empty_get()
{
	for (int i = 0;i<items;i++)
	{
		if (_node[i].is_empty)
		{
			return &_node[i];
		}
	}
	return nullptr;
}

template<typename T, int items>
bool List<T, items>::_node_is_more_important_than(Node * resident, Node * candidate)
{
	return (_order(&resident->data, &candidate->data));
}

template<typename T, int items>
bool List<T, items>::_node_is_connected(Node * node)
{
	return ((node->previous != nullptr) || (node->next != nullptr));
}

template<typename T, int items>
void List<T, items>::_node_attach_before(Node * resident, Node * candidate)
{
	if (resident->previous != nullptr)
	{
		resident->previous->next = candidate; // bind with former
		candidate->previous = resident->previous;

		candidate->next = resident; //bind with latter
		resident->previous = candidate;
	}
	else
	{
		_head = candidate;
		candidate->next = resident;
		resident->previous = candidate;
	}
}

template<typename T, int items>
void List<T, items>::_node_attach_after(Node * resident, Node * candidate)
{
	candidate->previous = resident;
	resident->next = candidate;
}

template<typename T, int items>
void List<T, items>::_node_deattach(Node * node)
{
	node->is_empty = true;

	if (_head == node)
	{
		if (node->next != nullptr)
		{
			node->next->previous = nullptr;
			_head = node->next;
		}
		else
		{
			_head = nullptr;
		}
	}
	else
	{
		if ((node->previous != nullptr) && (node->next != nullptr)) // both connected
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
		}
		else // at end
		{
			node->previous->next = nullptr;
		}
	}
}



#endif