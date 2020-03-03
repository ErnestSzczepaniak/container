#ifndef _iterable_h
#define _iterable_h

/*
* project:	container
* file:		iterable.h
* author:	en2
* date:		18-02-2020
*/

template<typename C, typename T>
class Iterator
{
public:
    Iterator(C * child, int iterator = 0);
    ~Iterator(); 

    void operator++();
    bool operator!=(const Iterator & rhs);
    const T & operator*();

private:
    C * _child;
    int _iterator;

}; /* class: Iterator */

template<typename C, typename T>
class Iterable
{
public:
    Iterable();
    ~Iterable();

    Iterator<C, T> begin();
    Iterator<C, T> end();

}; /* class: Iterable */

//---------------------------------------------| info |---------------------------------------------//

template<typename C, typename T>
Iterator<C, T>::Iterator(C * child, int iterator) 
:
_child(child),
_iterator(iterator)
{

}

template<typename C, typename T>
Iterator<C, T>::~Iterator()
{

}

template<typename C, typename T>
void Iterator<C, T>::operator++()
{
    _iterator++;
}

template<typename C, typename T>
bool Iterator<C, T>::operator!=(const Iterator<C, T> & rhs)
{
    return _iterator != rhs._iterator;
}

template<typename C, typename T>
const T & Iterator<C, T>::operator*()
{
    return _child->operator[](_iterator);
}

//---------------------------------------------| info |---------------------------------------------//

template<typename C, typename T>
Iterable<C, T>::Iterable()
{

}

template<typename C, typename T>
Iterable<C, T>::~Iterable()
{

}

template<typename C, typename T>
Iterator<C, T> Iterable<C, T>::begin()
{
    return {static_cast<C *>(this)};
}

template<typename C, typename T>
Iterator<C, T> Iterable<C, T>::end()
{
    return {static_cast<C *>(this), static_cast<C *>(this)->size_actual()};
}

#endif /*define: iterable_h*/