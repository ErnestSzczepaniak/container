#ifndef _container_iterator_h
#define _container_iterator_h

/*
* project:	container
* file:		container_iterator.h
* author:	en2
* date:		16-02-2020
*/

template<typename T, int size>
class Iterator
{
public:
    Iterator(T * data, int position, bool full);
    ~Iterator();

    T & operator*();
    Iterator & operator++();
    bool operator!=(const Iterator & rhs);

protected:
    

private:
    T * _data;
    int _position;
    bool _full;

}; /* class: Iterator */

template<typename T, int size>
Iterator<T, size>::Iterator(T * data, int position, int full)
:
_data(data),
_position(position),
_full(full)
{

}

template<typename T, int size>
Iterator<T, size>::~Iterator()
{

}

template<typename T, int size>
T & Iterator<T, size>::operator*()
{
    return _data[_position];
}

template<typename T, int size>
Iterator<T, size> & Iterator<T, size>::operator++()
{
    _position = (_position + 1) % size;
    return *this;
}

template<typename T, int size>
bool Iterator<T, size>::operator!=(const Iterator & rhs) // if false jump in loop
{
    if (_full)
    {

    }
    else
    {
        return _position != rhs._position;
    }
}





#endif /*define: container_iterator_h*/