#include "my_dll.h"
#include "singleton-cpp/singleton.h"

MY_DLL_API void setValue() {

    MyObject0 &obj0 = singleton<MyObject0>();
    obj0.a = 3;
    obj0.b = 4;

    MyObject1 &obj1 = singleton<MyObject1>();
    obj1.c = "test1234";
}
