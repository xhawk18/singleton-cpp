#pragma once
#ifndef INC_SINGLETON_H_
#define INC_SINGLETON_H_

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

template<typename T>
class Singleton;

// Get singleton instance
template<typename T>
inline T &singleton() {
    return Singleton<T>::getInstance();
}


struct SingleTonHolder {
    void *object_;
    std::shared_ptr<std::mutex> mutex_;
};

SINGLETON_API std::mutex &getSingleTonMutex();
SINGLETON_API SingleTonHolder *getSingleTonType(const std::type_index &typeIndex);


template<typename T>
class Singleton {
public:
    // Get the single instance
    static T &getInstance() {
        return *getInstancePrivate();
    }

private:
    // Get the single instance
    static T *getInstancePrivate() {
        static T *instance = nullptr;
        if (instance != nullptr)
            return instance;

        SingleTonHolder *singleTonHolder = nullptr;
        {
            // Locks and get the global mutex
            std::lock_guard<std::mutex> myLock(getSingleTonMutex());
            if (instance != nullptr)
                return instance;

            singleTonHolder = getSingleTonType(std::type_index(typeid(T)));
        }

        // Create single instance
        T *instanceFromHolder = createInstanceFromHolder(singleTonHolder);

        {
            // Save single instance object
            std::lock_guard<std::mutex> myLock(getSingleTonMutex());
            instance = instanceFromHolder;
            return instance;
        }
    }

    static T *createInstanceFromHolder(SingleTonHolder *singleTonHolder) {
        // Locks class T and make sure to call construction only once
        std::lock_guard<std::mutex> myLock(*singleTonHolder->mutex_);
        if (singleTonHolder->object_ == nullptr) {
            // construct the instance with static funciton
            singleTonHolder->object_ = reinterpret_cast<void *>(getStaticInstance());
        }
        return reinterpret_cast<T *>(singleTonHolder->object_);
    }

    static T *getStaticInstance() {
        static T t;
        return &t;
    }
};


#endif
