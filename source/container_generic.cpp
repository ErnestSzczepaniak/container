#include "container_generic.h"

Container_generic::Container_generic(int size_actual, int size_max) : _size_actual(size_actual), _size_max(size_max)
{

}

Container_generic::~Container_generic()
{

}

int Container_generic::size_actual()
{
    return _size_actual;
}

int Container_generic::size_max()
{
    return _size_max;
}

bool Container_generic::is_empty()
{
    return (_size_actual == 0);
}

bool Container_generic::is_full()
{
    return (_size_actual == _size_max);
}
