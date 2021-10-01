#include "my_dll.h"
#include "singleton-cpp/singleton.h"

int main() {
    // set value in dll
    setValue();

    // get value from exe
    MyObject0 &obj0 = singleton<MyObject0>();
    printf("%d %d\n", obj0.a, obj0.b);

    MyObject1 &obj1 = singleton<MyObject1>();
    printf("%s\n", obj1.c.c_str());

    return 0;
}
