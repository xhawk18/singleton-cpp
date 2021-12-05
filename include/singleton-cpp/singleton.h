#pragma once
#ifndef INC_SINGLETON_H_
#define INC_SINGLETON_H_

#include <cstdlib>
#include <mutex>
#include <typeindex>
#include <memory>
#include "singleton_api.h"

// Singleton mode for cpp
// 
// Features --
//   1. Works for both dynamical library and executable.
//   2. Multithread safe
//   3. Lazy consturction

SINGLETON_API void getSharedInstance(const std::type_index &typeIndex, 
                                     void *(*getStaticInstance)(),
                                     void *&instance);


template<typename T>
class Singleton {
public:
    // Get the single instance
    static T &getInstance() {
        static void *instance = NULL;
        if (instance == NULL)
            getSharedInstance(typeid(T), &getStaticInstance, instance);
        return *reinterpret_cast<T *>(instance);
    }

private:
    static void *getStaticInstance() {
        static T t;
        return reinterpret_cast<void *>(&reinterpret_cast<char &>(t));
    }
};

// Get singleton instance
template<typename T>
inline T &singleton() {
    return Singleton<T>::getInstance();
}


#endif
