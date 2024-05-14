/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Process.hpp
*/

#pragma once

#include <unistd.h>
#include <cstring>
#include <csignal>
#include <iostream>

#include "../Exceptions/Exceptions.hpp"

template <typename T>
class Process {
public:
    Process() {
        pid = fork();
        if (pid == -1)
            throw exceptions::ProcessError(std::strerror(errno));
        if (pid == 0)
            _core = T();
    }

    ~Process() {
        std::cout << "des\n";
        kill(pid, SIGQUIT);
    }

    pid_t pid;

private:
    T _core;
};
