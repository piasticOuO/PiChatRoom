//
// Created by piasticouo on 25-2-18.
//

#include <utility>

#include "../include/ThreadPool.h"

ThreadPool::ThreadPool(int size) : work_threads(size) {
    for (int i = 0; i < size; i++) {
        work_threads.emplace_back([this]() {
            while (true) {
                std::function<void()> task;
                {
                    std::unique_lock lock(queue_mutex);
                    condition.wait(lock, [this]{return stop_flag || !task_queue.empty();});
                    if (stop_flag) { return; }
                    task = task_queue.front();
                    task_queue.pop();
                }
                task();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    stop_flag = 1;
    condition.notify_all();
    for (auto &thread : work_threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void ThreadPool::enqueue(std::function<void()> task) {
    task_queue.push(std::move(task));
    condition.notify_one();
}