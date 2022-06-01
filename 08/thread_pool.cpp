#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t size)
{
    for (size_t i = 0; i < size; ++i)
        threads.emplace_back(std::thread([this]
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(_mutex);
                    task_condition.wait(lock, [this] { return !tasks.empty(); });
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                if (!task)
                {
                    task_stop();
                    return;
                }
                task();
            }
        }));
}

ThreadPool::~ThreadPool() 
{
    task_stop();
    for (auto& thread : threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
    std::queue<std::function<void()>> empty{};
    std::swap(tasks, empty);
}

void ThreadPool::task_stop()
{
    std::lock_guard<std::mutex> lock(_mutex);
    tasks.push(std::function<void()>{});
    task_condition.notify_one();
}
