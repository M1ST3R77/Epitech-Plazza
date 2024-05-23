/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** ThreadPool.cpp
*/

#include "ThreadPool.hpp"

#include "../Logger/Logger.hpp"

ThreadPool::ThreadPool(const size_t max_threads) :
    activeThreads(0), stop(false), _maxThreads(max_threads) {
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock(queueMutex);
        stop = true;
    }
    for (std::thread &worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    workers.clear();
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock lock(queueMutex);
        if (activeThreads < _maxThreads && activeThreads <= tasks.size()) {
            workers.emplace_back([this, task] { return this->workerThread(this->activeThreads, task); });
            ++activeThreads;
        } else {
            tasks.emplace(std::move(task));
        }
    }
}

void ThreadPool::workerThread(const size_t my_thread, const std::function<void()> &prior_task) {
    Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + ": Cook " + std::to_string(my_thread) + ": Started", Logger::Info);
    prior_task();
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock lock(queueMutex);
            if (tasks.empty() || stop) {
                --activeThreads;
                Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + ": Cook " + std::to_string(my_thread) + ": Stopped", Logger::Info);
                return;
            }
            if (!tasks.empty()) {
                task = std::move(tasks.front());
                tasks.pop();
            }
        }
        task();
    }
}
