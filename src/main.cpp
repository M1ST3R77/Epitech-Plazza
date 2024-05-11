/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** main.cpp
*/

#include <iostream>

#include "Shell.hpp"
#include "Exceptions.hpp"

int main(int ac, char **av)
{
    try {
        plazza::Shell shell(ac, av);
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
        return 84;
    }
    return 0;
}