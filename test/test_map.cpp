#include "test.h"
#include "map.h"
#include "priority_named_map.h"
#include "quantum_map.h"
#include "pointer_map.h"

struct Thread
{
    public:
    Thread(const char * name, int priority) : _name(name), _priority(priority) {}
    ~Thread() {}

    const char * name() {return _name;}
    int priority() {return _priority;}

    const char * _name;
    int _priority;
};



TEST_CASE("test_case_name")
{
    Thread t1("t1", 2);
    Thread t2("t2", 3);

    Priority_named_map<Thread, 32> map;

    map.add(&t1);
    map.add(&t2);

    REQUIRE(map.has_priority_grater_than(4) == false);
    REQUIRE(map.has_priority_grater_or_equal_than(3) == true);


    Quantum_map<Thread, 32> qmap;

    qmap.add(&t1, 3);

    qmap.quantum_tick();
    qmap.quantum_tick();
    qmap.quantum_tick();

    REQUIRE(qmap.quantum_reached_at_front() == true);

    auto * t = qmap.pop();

    REQUIRE(qmap.size_actual() == 0);

}