/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPC.hpp
*/

#pragma once
#include <string>
#include <vector>

class IPC {
public:
    IPC();
    ~IPC();

    IPC &operator<<(const std::string &message);
    IPC &operator>>(std::string &message);

    void destruct() const;

private:
    std::vector<int> fd;
};
