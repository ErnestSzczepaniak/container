#ifndef _container_queue_h
#define _container_queue_h

/*
* project:	container
* file:		container_queue.h
* author:	en2
* date:		16-02-2020
*/

#include "container_generic.h"
#include "container_iterator.h"

#define __index_front ((_head >= _size_actual) ? _head - _size_actual : _head + size - _size_actual)
#define __index_back (_head != 0 ? _head - 1 : size - 1)

template<typename T = int, int size = 32>
class Container_queue : public Container_generic
{
public:
    Container_queue();
    ~Container_queue();

    void push(const T & item);
    void pop();

    const T & front();
    const T & back();

    Iterator<T, size> begin() { return {_item, __index_front, false};}
    Iterator<T, size> end() { return {_item, _head, true};}

protected:
    

private:
    T _item[size];

    int _head;

}; /* class: Container_queue */

template<typename T, int size>
Container_queue<T, size>::Container_queue()
:
Container_generic(0, size),
_head(0)
{

}

template<typename T, int size>
Container_queue<T, size>::~Container_queue()
{
    
}

template<typename T, int size>
void Container_queue<T, size>::push(const T & item)
{
    _item[_head] = item;
    _head = (_head + 1) % size;

    if (_size_actual < size) _size_actual++;
}

template<typename T, int size>
void Container_queue<T, size>::pop()
{
    if (_size_actual > 0) _size_actual--;
}

template<typename T, int size>
const T & Container_queue<T, size>::front()
{
    return _item[__index_front];
}

template<typename T, int size>
const T & Container_queue<T, size>::back()
{
    return _item[__index_back];
}

#endif /*define: container_queue_h*/