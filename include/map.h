#ifndef _map_h
#define _map_h

#include "string.h"
#include <type_traits>

template<typename T = int, int items = 32, typename K = const char *>
class Map
{
    struct Node {bool is_empty; K key; T item; Node * previous; Node * next;};
    struct Result {K key; T item;};

public:
    Map();
    ~Map();

    int size_actual();
    int size_max();

    bool is_empty();
    bool is_full();

    bool add(K key, const T & item);
    bool has(K key);
    T * peek(K key);
    Result remove(K key);

    Result pop();

    T * at(int index);
    T * front();
    T * back();

protected:
    inline bool _node_matches_key(Node * resident, K key);
    inline Node * _node_find(K key);

    inline void _node_attach_after(Node * resident, Node * candidate);
    inline void _node_attach_before(Node * resident, Node * candidate);
    inline void _node_deattach(Node * resident);

private:
    Node * _head;
    Node _node[items];
    int _size_actual;
};

//---------------------------------------------| info |---------------------------------------------//

template<typename T, int items, typename K>
Map<T, items, K>::Map()
:
_head(nullptr), 
_size_actual(0)
{
    for (int i = 0; i < items; i++) _node[i].is_empty = true;
}

template<typename T, int items, typename K>
Map<T, items, K>::~Map()
{

}

template<typename T, int items, typename K>
int Map<T, items, K>::size_actual()
{
    return _size_actual;
}

template<typename T, int items, typename K>
int Map<T, items, K>::size_max()
{
    return items;
}

template<typename T, int items, typename K>
bool Map<T, items, K>::is_empty()
{
    return (_size_actual == 0);
}

template<typename T, int items, typename K>
bool Map<T, items, K>::is_full()
{
    return (_size_actual == items);
}

template<typename T, int items, typename K>
bool Map<T, items, K>::add(K key, const T & item)
{
    if (auto * node = _node_find(key); node != nullptr)
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

template<typename T, int items, typename K>
typename Map<T, items, K>::Result Map<T, items, K>::pop()
{
    if (_size_actual > 0)
    {
        auto result = _head->item;
        auto key = _head->key;

        _node_deattach(_head);

        return {key, result};
    }

    if constexpr (std::is_same_v<K, const char *>)
    {
        return {nullptr, {}};
    }
    else if constexpr (std::is_same_v<K, int>)
    {
        return {0, {}};
    }
    else
    {
        return {{}, {}};
    }
}

template<typename T, int items, typename K>
typename Map<T, items, K>::Result Map<T, items, K>::remove(K key)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_key(current, key))
        {
            auto result = current->item;
            auto key = current->key;

            _node_deattach(current);

            return {key, result};
        }
        else current = current->next;
    }

    if constexpr (std::is_same_v<K, const char *>)
    {
        return {nullptr, {}};
    }
    else if constexpr (std::is_same_v<K, int>)
    {
        return {0, {}};
    }
    else
    {
        return {{}, {}};
    }
}

template<typename T, int items, typename K>
T * Map<T, items, K>::peek(K key)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_key(current, key)) return &current->item;
        else current = current->next;
    }

    return nullptr;
}

template<typename T, int items, typename K>
T * Map<T, items, K>::at(int index)
{
    if (_size_actual > index)
    {
        auto * current = _head;

        for (int i = 0; i < index; i++) current = current->next;
        return &current->item;
    }
    else return nullptr;
}

template<typename T, int items, typename K>
T * Map<T, items, K>::front()
{
    return at(0);
}

template<typename T, int items, typename K>
T * Map<T, items, K>::back()
{
    return at(_size_actual);
}

template<typename T, int items, typename K>
bool Map<T, items, K>::has(K key)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_key(current, key)) return true;
        else current = current->next;
    }

    return false;
}

//---------------------------------------------| info |---------------------------------------------//

template<typename T, int items, typename K>
bool Map<T, items, K>::_node_matches_key(Node * resident, K key)
{
    if constexpr (std::is_same_v<K, const char *>)
    {
        return (strcmp(resident->key, key) == 0);
    }
    else
    {   
        return (resident->key == key);
    }
}

template<typename T, int items, typename K>
typename Map<T, items, K>::Node * Map<T, items, K>::_node_find(K key)
{
    auto * current = _head;

    for (int i = 0; i < _size_actual; i++)
    {
        if (_node_matches_key(current, key)) return nullptr;
        else current = current->next;
    }

    for (int i = 0; i < items; i++)
    {
        if (_node[i].is_empty)
        {
            _node[i].is_empty = false;
            _node[i].key = key;
            _node[i].previous = nullptr;
            _node[i].next = nullptr;
            return &_node[i];
        } 
    }

    return nullptr;
}

template<typename T, int items, typename K>
void Map<T, items, K>::_node_attach_after(Node * resident, Node * candidate)
{
	candidate->previous = resident;
	resident->next = candidate;

    _size_actual++;
}

template<typename T, int items, typename K>
void Map<T, items, K>::_node_deattach(Node * node)
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