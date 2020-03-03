#include "test.h"
#include "container_queue.h"

TEST_CASE("dw")
{
    Container_queue<int, 4> q;

    for (int i = 0; i < 3; i++)
    {
        q.push(10);
    }

    for (int i = 0; i < 3; i++)
    {
        q.pop();
    }

    for (int i = 0; i < 6; i++)
    {
        q.push(i);
    }

    for (auto && a : q)
    {
        printf("a =  %d\n", a);
    }

    // for (int i = 0; i < 10; i++)
    // {
    //     q.push(1);
    //     REQUIRE(q.back() == 1);
    //     q.push(2);
    //     REQUIRE(q.back() == 2);
    //     q.push(3);
    //     REQUIRE(q.back() == 3);

    //     auto a1 = q.front();
    //     q.pop();
    //     auto a2 = q.front();
    //     q.pop();
    //     auto a3 = q.front();
    //     q.pop();

    //     REQUIRE(a1 == 1);
    //     REQUIRE(a2 == 2);
    //     REQUIRE(a3 == 3);
    // }

    // for (auto a : q)
    // {
    //     printf("a =  %d\n", a);
    // }

}