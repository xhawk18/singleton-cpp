#pragma once
#ifndef INC_MY_DLL_H_
#define INC_MY_DLL_H_

#include "my_dll_api.h"
#include <string>

class MyObject0 {
public:
    int a;
    int b;
};

class MyObject1 {
public:
    std::string c;
};


MY_DLL_API void setValue();


#endif
