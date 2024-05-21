/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool.hpp
*/

#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t max_threads);
    ~ThreadPool();

    void enqueue(std::function<void()>);

private:
    void workerThread(size_t my_thread, const std::function<void()> &prior_task);

    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
    std::atomic<size_t> activeThreads;
    size_t _maxThreads;
};
