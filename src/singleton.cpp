#include "singleton-cpp/singleton.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

namespace {
struct SingleTonHolder {
    void *object_;
    std::shared_ptr<std::mutex> mutex_;
};
}

// Global mutex
static std::mutex &getSingleTonMutex() {
    // s_singleTonMutex is not 100% safety for multithread
    // but if there's any singleton object used before thread, it's safe enough.
    static std::mutex s_singleTonMutex;
    return s_singleTonMutex;
}

static SingleTonHolder *getSingleTonType(const std::type_index &typeIndex) {
    static std::unordered_map<std::type_index, SingleTonHolder> s_singleObjects;

    // Check the old value
    std::unordered_map<std::type_index, SingleTonHolder>::iterator itr = s_singleObjects.find(typeIndex);
    if (itr != s_singleObjects.end())
        return &itr->second;

    // Create new one if no old value
    std::pair<std::type_index, SingleTonHolder> singleHolder( 
        typeIndex,
        SingleTonHolder()
    );
    itr = s_singleObjects.insert(singleHolder).first;
    SingleTonHolder &singleTonHolder = itr->second;
    singleTonHolder.object_ = NULL;
    singleTonHolder.mutex_ = std::shared_ptr<std::mutex>(new std::mutex());

    return &singleTonHolder;
}

SINGLETON_API void getSharedInstance(const std::type_index &typeIndex,
                                     void *(*getStaticInstance)(),
                                     void *&instance) {
    // Get the single instance
    SingleTonHolder *singleTonHolder = NULL;
    {
        // Locks and get the global mutex
        std::lock_guard<std::mutex> myLock(getSingleTonMutex());
        if (instance != NULL)
            return;
        
        singleTonHolder = getSingleTonType(typeIndex);
    }

    // Create single instance
    {
        // Locks class T and make sure to call construction only once
        std::lock_guard<std::mutex> myLock(*singleTonHolder->mutex_);
        if (singleTonHolder->object_ == NULL) {
            // construct the instance with static funciton
            singleTonHolder->object_ = (*getStaticInstance)();
        }
    }    

    // Save single instance object
    {
        std::lock_guard<std::mutex> myLock(getSingleTonMutex());
        instance = singleTonHolder->object_;
    }
}

