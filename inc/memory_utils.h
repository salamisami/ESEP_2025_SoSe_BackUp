#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <memory> // for std::unique_ptr

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


#endif
