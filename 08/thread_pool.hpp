#pragma once

#include <queue>
#include <functional>
#include <queue>

#include <condition_variable>
#include <mutex>
#include <thread>
#include <type_traits>
#include <future>


class ThreadPool 
{
public:
    explicit ThreadPool(size_t size = std::thread::hardware_concurrency());
    ~ThreadPool();
    template <typename Func, typename... Args>
    auto exec(Func&& func2, Args&&... args);
private:
    std::queue<std::function<void()>> tasks;
    std::mutex _mutex;
    std::vector<std::thread> threads;
    std::condition_variable task_condition;

    void task_stop();
};

#include "thread_pool.tpp"
