#ifndef _container_generic_h
#define _container_generic_h

/*
* project:	container
* file:		container_generic.h
* author:	en2
* date:		06-02-2020
*/

class Container_generic
{
public:
    Container_generic(int size_actual, int size_max);
    ~Container_generic();

    int size_actual();
    int size_max();

    bool is_empty();
    bool is_full();

protected:
    int _size_actual;
    int _size_max;
  

}; /* class: Container_generic */

#endif /* define: container_generic_h */