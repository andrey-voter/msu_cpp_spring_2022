#pragma once


template <typename Func, typename... Args>
auto ThreadPool::exec(Func&& func2, Args&&... args)
{
    auto task = std::make_shared<std::packaged_task<typename std::result_of<Func(Args...)>::type()>>(std::bind(std::forward<Func>(func2), std::forward<Args>(args)...));
    auto res = task->get_future();
    {
        std::lock_guard<std::mutex> lock(_mutex);
        tasks.emplace([task] { (*task)(); });
    }
    task_condition.notify_one();
    return res;
}
