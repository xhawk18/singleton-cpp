## cpp singleton that works across dll/exe boundaries.

Features --

1. Share the same singleton instance in dynamical library and executable.
2. Multithread safe
3. Lazy construction
4. Lock-free with double checked mutex on initialization.

## Usage

1. define a class or struct, for example

```
class MyObject {
public:
    int a;
    int b;
};
```

2. use the singleton instance

```
#include "singleton-cpp/singleton.h"

MyObject &obj = singleton<MyObject>();
```
