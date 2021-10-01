## Singleton for cpp

Features --

1. Works for both dynamical library and executable.
2. Multithread safe
3. Lazy consturction

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
    MyObject &obj = singleton<MyObject>();
```
