/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** ProcessPool.hpp
*/

#pragma once

#include <cstring>
#include <functional>
#include <iostream>
#include <sys/wait.h>
#include <vector>

#include "../Exceptions/Exceptions.hpp"
#include "../IPC/IPC.hpp"

class ProcessPool {
public:
    ProcessPool() = default;

    ~ProcessPool();

    template <typename Func>
    pid_t addProcess(Func &&func) {
        processes.emplace(std::piecewise_construct, std::forward_as_tuple(0), std::forward_as_tuple());
        const pid_t pid = fork();
        if (pid == 0) {
            func(processes[0]);
            exit(0);
        }
        if (pid < 0)
            throw exceptions::ProcessError(std::string("fork: ") + std::strerror(errno));
        auto nodeHandle = processes.extract(0);
        if (!nodeHandle.empty()) {
            nodeHandle.key() = pid;
            processes.insert(std::move(nodeHandle));
        }
        return pid;
    }

    int endProcess(pid_t pid) const;

    std::unordered_map<pid_t, std::pair<IPC, IPC>> processes{};
};
