/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include "Main.hpp"

void plazza::Shell::help_parsing() {
    std::cout << "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*\n"
        "TYPE := [a..zA..Z]+\n"
        "SIZE := S|M|L|XL|XXL\n"
        "NUMBER := x[1..9][0..9]*\n";
}

void plazza::Shell::parsing(const int ac, const std::vector<std::string_view> &av) {
    if (ac != 4)
        throw exceptions::ParamsError(ac < 4 ? "Not enough parameters" : "Too many parameters");
    try {
        _mult = std::stof(std::string(av[1]));
        _nb_cooks = std::stoi(std::string(av[2]));
        _time = std::stoi(std::string(av[3]));
    } catch (const std::invalid_argument &) {
        throw exceptions::ParamsError("Bad arguments");
    } catch (const std::out_of_range &) {
        throw exceptions::ParamsError("Bad arguments");
    }
    if (_time <= 0 || _nb_cooks <= 0 || _mult < 0.0)
        throw exceptions::ParamsError("Bad arguments");
}

plazza::Shell::Shell(const int ac, const std::vector<std::string_view> &av) {
    parsing(ac, av);
    std::string cmd;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, cmd))
            break;
        if (cmd == "exit")
            break;
        if (cmd == "help")
            help_parsing();
    }
}
