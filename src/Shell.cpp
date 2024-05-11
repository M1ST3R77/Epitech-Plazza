/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include <iostream>
#include "Shell.hpp"
#include "Exceptions.hpp"

void plazza::Shell::help(void)
{
    std::cout << "USAGE\n\t./plazza m c t\n\nDESCRIPTION" << std::endl;
    std::cout << "\tm multiplier for the cooking time of the pizzas (>= 0)" << std::endl;
    std::cout << "\tc number of cooks per kitchen (> 0)" << std::endl;
    std::cout << "\tt the time, in milliseconds, used by the kitchen stock to replace ingredients (> 0)" << std::endl;
    exit(0);
}

void plazza::Shell::parsing(int ac, char **av)
{
    if (ac == 2 && std::string_view(av[1]) == "--help")
        help();
    if (ac != 4)
        throw exceptions::ParamsError(ac < 4 ? "Not enough parameters" : "Too many parameters");
    try {
        _Mult = std::stof(av[1]);
        _NbCooks = std::stoi(av[2]);
        _Time = std::stoi(av[3]);
    } catch (...) {
        throw exceptions::ParamsError("Bad arguments");
    }
    if (_Time <= 0 || _NbCooks <= 0 || _Mult < 0)
        throw exceptions::ParamsError("Bad arguments");
}

plazza::Shell::Shell(int ac, char **av)
{
    parsing(ac, av);
    std::string input;

    while (1) {
        if (!std::getline(std::cin, input))
            break;
        std::cout << "You write: " + input << std::endl;
    }
}