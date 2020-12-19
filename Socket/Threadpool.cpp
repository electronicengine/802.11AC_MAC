//
// Created by cenkerkaraors on 15.12.2020.
//
#include "Threadpool.h"
#include <future>

Threadpool::Threadpool(int Size)
{
    for(int i=0; i < Size; i++)
    {

        std::cout << "Thread " << i << " created" << std::endl;


        int thread_id = i;

        Workers_.emplace_back([=]()
                              {

                                  std::function<void()> task;

                                  while(true)
                                  {

                                      {

                                          std::unique_lock<std::mutex> ul(mutexLock);

                                          Condition_.wait(ul, [=]{ return !Tasks_.empty(); });

                                          task = std::move(Tasks_.front());
                                          Tasks_.pop();
                                          activeWorkers += 1;
                                          std::this_thread::sleep_for(std::chrono::seconds(1));

                                      }

                                      std::cout << "Thread " << thread_id << " is working" << std::endl;
                                      task();
                                      {
                                          std::unique_lock<std::mutex> ul(mutexLock);
                                          activeWorkers -=1;
                                      }
                                  }

                              });
    }

}

Threadpool::~Threadpool(){
    std::cout << "Destructed" << std::endl;
    stop();
}

void Threadpool::stop(){
    std::cout << "Start: " << Workers_.size() << std::endl;

    {
        std::unique_lock<std::mutex> lock{mutexLock};
        mStoping = true;

    }
    Condition_.notify_all();

    //std::cout << "Notfied" << std::endl;
    for(auto &item: Workers_)
    {
        //std::cout << "Item" << std::endl;
        item.join();
    }


    std::cout << "Stop" << std::endl;

}

