//
// Created by cenkerkaraors on 14.12.2020.
//

#ifndef UNIX_SOCKET_THREADPOOL_H
#define UNIX_SOCKET_THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <functional>
#include <condition_variable>
#include <memory>
#include <future>
#include <stdexcept>
#include <iostream>
#include <chrono>


class Threadpool
{

    std::condition_variable Condition_;
    std::vector<std::thread> Workers_;
    std::queue<std::function<void()>> Tasks_;
    std::mutex mutexLock;
    int activeWorkers = 0;

public:
    explicit Threadpool(int Size);
    ~Threadpool();
    bool mStoping = false;

    void stop();

    int getWorkerSize()
    {
        return Workers_.size();
    }

    int getActiveWorkers()
    {
        return activeWorkers;
    }


    template<class F, class ...ARG>
    auto pushWork(F && Func, ARG &&... Args)
    -> std::future<typename std::result_of<F(ARG...)>::type>
    {
        using return_type = typename std::result_of<F(ARG...)>::type;

        auto packaged_func = std::make_shared<std::packaged_task<return_type()>>(
                std::bind(std::forward<F>(Func), std::forward<ARG>(Args)...)
        );

        Tasks_.emplace([=]{(*packaged_func)(); });

        std::future<return_type> response = packaged_func->get_future();

        Condition_.notify_one();

        return response;

    }

};
#endif //UNIX_SOCKET_THREADPOOL_H
