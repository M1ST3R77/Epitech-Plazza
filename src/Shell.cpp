/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include <iostream>

#include "Shell.hpp"
#include "Exceptions.hpp"
#include "define.hpp"

void plazza::Shell::help(void)
{
    std::cout << "USAGE\n\t./plazza m c t\n\nDESCRIPTION" << std::endl;
    std::cout << "\tm multiplier for the cooking time of the pizzas (>= 0)" << std::endl;
    std::cout << "\tc number of cooks per kitchen (> 0)" << std::endl;
    std::cout << "\tt the time, in milliseconds, used by the kitchen stock to replace ingredients (> 0)" << std::endl;
    exit(SUCCESS_RETURN);
}

void plazza::Shell::help_parsing(void)
{
    std::cout << "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*" << std::endl;
    std::cout << "TYPE := [a..zA..Z]+" << std::endl;
    std::cout << "SIZE := S|M|L|XL|XXL" << std::endl;
    std::cout << "NUMBER := x[1..9][0..9]*" << std::endl;
}

void plazza::Shell::parsing(int ac, std::vector<std::string_view> av)
{
    if (ac == 2 && av[1] == "--help")
        help();
    if (ac != 4)
        throw exceptions::ParamsError(ac < 4 ? "Not enough parameters" : "Too many parameters");
    try {
        _Mult = std::stof(std::string(av[1]));
        _NbCooks = std::stoi(std::string(av[2]));
        _Time = std::stoi(std::string(av[3]));
    } catch (const std::invalid_argument &) {
        throw exceptions::ParamsError("Bad arguments");
    } catch (const std::out_of_range &) {
        throw exceptions::ParamsError("Bad arguments");
    }
    if (_Time <= 0 || _NbCooks <= 0 || _Mult < 0)
        throw exceptions::ParamsError("Bad arguments");
}

plazza::Shell::Shell(int ac, std::vector<std::string_view> av)
{
    parsing(ac, av);
    std::string cmd;

    while (1) {
        std::cout << "> ";
        if (!std::getline(std::cin, cmd))
            break;
        if (cmd == "exit")
            break;
        else if (cmd == "help")
            help_parsing();
    }
}