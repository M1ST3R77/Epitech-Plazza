/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** ThreadPool.cpp
*/

#include "ThreadPool.hpp"

#include <iostream>


ThreadPool::ThreadPool(const size_t maxThreads) :
    stop(false), activeThreads(0), _maxThreads(maxThreads) {
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock(queueMutex);
        stop = true;
    }
    condition.notify_all();
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
        tasks.emplace(std::move(task));
    }
    condition.notify_one();
    {
        std::unique_lock lock(queueMutex);
        if (activeThreads < _maxThreads && activeThreads <= tasks.size()) {
            workers.emplace_back(&ThreadPool::workerThread, this);
            ++activeThreads;
        }
    }
}

void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock lock(queueMutex);
            if (tasks.empty() || stop) {
                --activeThreads;
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
