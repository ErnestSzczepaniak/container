#include "test.h"
#include "map.h"

TEST_CASE("test_case_name")
{
    int k = 2;
    int s = 3;

    Map<int, 32, const char *> map;

    map.add("dwa", 2);
    map.add("trzy", 3);

    map.remove("dwa");

    auto [key, value] = map.remove("trzy"); 

}