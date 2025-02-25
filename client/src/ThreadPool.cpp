//
// Created by piasticouo on 25-2-18.
//

#include <utility>

#include "../include/ThreadPool.h"

ThreadPool::ThreadPool(int size) : work_threads(size) {
    for (int i = 0; i < size; i++) {
        work_threads.emplace_back([this]() {
            while (true) {
                if (stop_flag) break;
                std::function<void()> task;
                task = task_queue.pop();
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop_flag = 1;
}

void ThreadPool::enqueue(std::function<void()> task) {
    task_queue.push(std::move(task));
}