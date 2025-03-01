//
// Created by piasticouo on 25-2-18.
//

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP
#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
#include <queue>

class ThreadPool {
public:
   explicit ThreadPool(int size);
   ~ThreadPool();
   void enqueue(std::function<void()> task);
private:
   std::vector<std::thread> work_threads;
   std::queue<std::function<void()>> task_queue;
   std::mutex queue_mutex;
   std::condition_variable condition;
   int stop_flag{};
};

#endif //THREADPOOL_HPP
