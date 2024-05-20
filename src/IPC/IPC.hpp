/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPC.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "../Exceptions/Exceptions.hpp"

class IPC {
public:
    IPC();
    ~IPC();

    IPC &operator<<(const std::string &message);
    IPC &operator>>(std::string &message);

    template<typename T>
    IPC &operator<<(const T &message) {
        if (write(fd[1], &message, sizeof(message)) == -1)
            throw exceptions::ProcessError(std::string("Can't write on fd ") + std::to_string(fd[1]));
        return *this;
    }

    template<typename T>
    IPC &operator>>(T &message) {
        constexpr int buf_size = sizeof(message);
        const ssize_t len = read(fd[0], &message, buf_size);
        if (len == 0)
            std::cerr << "End of file on fd " << fd[0] << std::endl;
        if (len < 0)
            throw exceptions::ProcessError(std::string("Can't read on fd ") + std::to_string(fd[0]));
        return *this;
    }

    void destruct() const;
    [[nodiscard]] bool contentReadable() const;

private:
    std::vector<int> fd;
};
