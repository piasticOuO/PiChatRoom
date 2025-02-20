//
// Created by piasticouo on 25-2-16.
//

#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H
#include <mutex>
#include <queue>

template<class T>
class SafeQueue {
    std::queue<T> q;
    std::mutex mtx;
public:
    void push(T x);
    T pop();
    bool empty();
};

#endif //SAFEQUEUE_H
