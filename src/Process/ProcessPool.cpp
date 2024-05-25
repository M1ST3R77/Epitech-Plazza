/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** ProcessPool.cpp
*/

#include "ProcessPool.hpp"

#include <csignal>

ProcessPool::~ProcessPool() = default;

bool ProcessPool::checkProcessIsAlive(const pid_t pid) const {
    return processes.contains(pid) && kill(pid, 0) != -1;
}
