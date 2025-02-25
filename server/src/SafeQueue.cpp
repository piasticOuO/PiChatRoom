//
// Created by piasticouo on 25-2-16.
//

#include "../include/SafeQueue.h"

template<class T>
T SafeQueue<T>::pop() {
    std::lock_guard lock(mtx);
    T x = q.front();
    q.pop();
    return x;
}

template<class T>
void SafeQueue<T>::push(T x) {
    std::lock_guard lock(mtx);
    q.push(x);
}

template<class T>
bool SafeQueue<T>::empty() {
    std::lock_guard lock(mtx);
    return q.empty();
}
