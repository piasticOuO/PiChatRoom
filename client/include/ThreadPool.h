//
// Created by piasticouo on 25-2-18.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H
#include <functional>
#include <thread>
#include <vector>

#include "../include/SafeQueue.h"

class ThreadPool {
   std::vector<std::thread> work_threads;
   SafeQueue<std::function<void()>> task_queue;
   int stop_flag{};
   public:
   explicit ThreadPool(int size);
   ~ThreadPool();
   void enqueue(std::function<void()> task);
};

#endif //THREADPOOL_H
