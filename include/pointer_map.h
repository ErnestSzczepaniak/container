#ifndef _pointer_map_h
#define _pointer_map_h

#include "string.h"

template<typename T = int, int items = 32>
class Pointer_map
{
    struct Node {bool is_empty; T * item; Node * previous; Node * next;};

public:
    Pointer_map();
    ~Pointer_map();

    int size_actual();
    int size_max();

    bool is_empty();
    bool is_full();

    bool add(const char * name, T * item);
    bool has(const char * name);
    T * peek(const char * name);
    T * remove(const char * name);

    T * pop();

    T * at(int index);
    T * front();
    T * back();

protected:
    inline bool _node_matches_name(Node * resident, const char * name);
    inline Node * _node_find(const char * name);

    inline void _node_attach_after(Node * resident, Node * candidate);
    inline void _node_attach_before(Node * resident, Node * candidate);
    inline void _node_deattach(Node * resident);

private:
    Node * _head;
    Node _node[items];
    int _size_actual;
};

//---------------------------------------------| info |---------------------------------------------//

template<typename T, int items>
Pointer_map<T, items>::Pointer_map()
:
_head(nullptr), 
_size_actual(0)
{
    for (int i = 0; i < items; i++) _node[i].is_empty = true;
}

template<typename T, int items>
Pointer_map<T, items>::~Pointer_map()
{

}

template<typename T, int items>
int Pointer_map<T, items>::size_actual()
{
    return _size_actual;
}

template<typename T, int items>
int Pointer_map<T, items>::size_max()
{
    return items;
}

template<typename T, int items>
bool Pointer_map<T, items>::is_empty()
{
    return (_size_actual == 0);
}

template<typename T, int items>
bool Pointer_map<T, items>::is_full()
{
    return (_size_actual == items);
}

template<typename T, int items>
bool Pointer_map<T, items>::add(const char * name, T * item)
{
    if (auto * node = _node_find(name); node != nullptr)
    {
        node->item = item;

        if (_head != nullptr)
        {
            auto * current = _head;

            while(true)
            {
                if (current->next == nullptr)
                {
                    _node_attach_after(current, node); break;
                }
                else
                {
                    current = current->next;
                }
            }
        }
        else
        {
            _head = node;
            _size_actual++;
        }   

        return true;
    }

    return false;
}

template<typename T, int items>
T * Pointer_map<T, items>::pop()
{
    if (_size_actual > 0)
    {
        auto result = _head->item;

        _node_deattach(_head);

        return result;
    }

    return nullptr;
}

template<typename T, int items>
T * Pointer_map<T, items>::remove(const char * name)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_name(current, name))
        {
            auto result = current->item;
 
            _node_deattach(current);

            return result;
        }
        else current = current->next;
    }

    return nullptr;
}

template<typename T, int items>
T * Pointer_map<T, items>::peek(const char * name)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_name(current, name)) return current->item;
        else current = current->next;
    }

    return nullptr;
}

template<typename T, int items>
T * Pointer_map<T, items>::at(int index)
{
    if (_size_actual > index)
    {
        auto * current = _head;

        for (int i = 0; i < index; i++) current = current->next;
        return current->item;
    }
    else return nullptr;
}

template<typename T, int items>
T * Pointer_map<T, items>::front()
{
    return at(0);
}

template<typename T, int items>
T * Pointer_map<T, items>::back()
{
    return at(_size_actual);
}

template<typename T, int items>
bool Pointer_map<T, items>::has(const char * name)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_name(current, name)) return true;
        else current = current->next;
    }

    return false;
}

//---------------------------------------------| info |---------------------------------------------//

template<typename T, int items>
bool Pointer_map<T, items>::_node_matches_name(Node * resident, const char * name)
{
    return resident->item->name.equals(name);
    //return (strcmp(resident->item->name(), name) == 0);
}

template<typename T, int items>
typename Pointer_map<T, items>::Node * Pointer_map<T, items>::_node_find(const char * name)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_name(current, name)) return nullptr;
        else current = current->next;
    }

    for (int i = 0; i < items; i++)
    {
        if (_node[i].is_empty)
        {
            _node[i].is_empty = false;
            _node[i].previous = nullptr;
            _node[i].next = nullptr;
            return &_node[i];
        } 
    }

    return nullptr;
}

template<typename T, int items>
void Pointer_map<T, items>::_node_attach_after(Node * resident, Node * candidate)
{
	candidate->previous = resident;
	resident->next = candidate;

    _size_actual++;
}

template<typename T, int items>
void Pointer_map<T, items>::_node_deattach(Node * node)
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
		if ((node->previous != nullptr) && (node->next != nullptr))
		{
			node->previous->next = node->next;
			node->next->previous = node->previous;
		}
		else
		{
			node->previous->next = nullptr;
		}
	}

    _size_actual--;
}

#endif