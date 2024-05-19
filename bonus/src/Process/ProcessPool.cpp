/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** ProcessPool.cpp
*/

#include "ProcessPool.hpp"

#include <iostream>
#include <ranges>

ProcessPool::~ProcessPool() {
    if (processes.contains(0))
        return;
    for (const pid_t pid : std::ranges::views::keys(processes)) {
        if (const int process_ret_val = endProcess(pid); process_ret_val > 0)
            std::cerr << "Kitchen " << pid << " returned " << process_ret_val << std::endl;
    }
}

int ProcessPool::endProcess(const pid_t pid) const {
    if (pid == 0 || !processes.contains(pid))
        return -1;
    int status;
    if (waitpid(pid, &status, 0) == -1)
        throw exceptions::ProcessError(std::string("waitpid: ") + std::strerror(errno));
    return WEXITSTATUS(status);
}
