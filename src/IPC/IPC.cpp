/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPC.cpp
*/

#include <iostream>
#include <unistd.h>

#include "IPC.hpp"
#include "../Exceptions/Exceptions.hpp"

IPC::IPC() :
    fd(std::vector(2, 0)) {
    pipe(fd.data());
}

IPC::~IPC() {
    destruct();
}

IPC &IPC::operator<<(const std::string &message) {
    if (write(fd[1], message.c_str(), message.length()) == -1)
        throw exceptions::ProcessError(std::string("Can't write on fd ") + std::to_string(fd[1]));
    return *this;
}

IPC &IPC::operator>>(std::string &message) {
    constexpr int buf_size = 3000;
    char buffer[buf_size + 1] = {};
    ssize_t len;
    message.clear();
    while ((len = read(fd[0], buffer, buf_size)) == buf_size)
        message.append(buffer);
    message.append(buffer);
    if (len == 0)
        std::cerr << "End of file on fd " << fd[0] << std::endl;
    if (len < 0)
        throw exceptions::ProcessError(std::string("Can't read on fd ") + std::to_string(fd[0]));
    return *this;
}

void IPC::destruct() const {
    close(fd[0]);
    close(fd[1]);
}
