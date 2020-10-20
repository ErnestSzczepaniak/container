#ifndef _ring_h
#define _ring_h

/**
 * @file	ring.h
 * @author	en2
 * @date	17-09-2020
 * @brief	
 * @details	
**/

template<typename T = int, int size = 32>
class Ring
{
public:
    Ring();
    ~Ring();

    int size_actual();
    int size_max();

    Ring & push(T value);

    T pop_back();
    T pop_front();

    T & at(int index);

protected:
    int _index_front();
    int _index_back();

private:
    int _size_actual = 0;
    int _head = 0;
    int _tail = 0;
    
    T _buffer[size];

}; /* class: Ring */

template<typename T, int size> 
Ring<T, size>::Ring()
{

}

template<typename T, int size> 
Ring<T, size>::~Ring()
{

}

template<typename T, int size> 
int Ring<T, size>::size_actual()
{
    return _size_actual;
}

template<typename T, int size> 
int Ring<T, size>::size_max()
{
    return size;
}

template<typename T, int size> 
Ring<T, size> & Ring<T, size>::push(T value)
{
    _buffer[_head] = value;
    _head = (_head + 1) % size;

    if (_size_actual < size) _size_actual++;

    return *this;
}

template<typename T, int size> 
T Ring<T, size>::pop_back()
{

}

template<typename T, int size> 
T Ring<T, size>::pop_front()
{

}

template<typename T, int size> 
T & Ring<T, size>::at(int index)
{

}

/* ---------------------------------------------| info |--------------------------------------------- */

template<typename T, int size> 
int Ring<T, size>::_index_front()
{

}

template<typename T, int size> 
int Ring<T, size>::_index_back()
{

}


#endif /* define: ring_h */