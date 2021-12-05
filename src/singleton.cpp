#include "singleton-cpp/singleton.h"
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

// Global mutex
SINGLETON_API std::mutex &getSingleTonMutex() {
    // s_singleTonMutex is not 100% safety for multithread
    // but if there's any singleton object used before thread, it's safe enough.
    static std::mutex s_singleTonMutex;
    return s_singleTonMutex;
}

SINGLETON_API SingleTonHolder *getSingleTonType(const std::type_index &typeIndex) {
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
