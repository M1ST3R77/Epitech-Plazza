/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include "Main.hpp"
#include "Utils.hpp"
#include "NPlazza.hpp"

void plazza::Shell::helpParsing() {
    std::cout << "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*\n"
        "TYPE := [a..zA..Z]+\n"
        "SIZE := S|M|L|XL|XXL\n"
        "NUMBER := x[1..9][0..9]*\n";
}

void plazza::Shell::parsing(const int ac, const std::vector<std::string_view> &av) {
    if (ac != 4)
        throw exceptions::ParamsError(ac < 4 ? "Not enough parameters" : "Too many parameters");
    try {
        _mult = str_to_float(std::string(av[1]));
        _nb_cooks = str_to_int(std::string(av[2]));
        _time = str_to_int(std::string(av[3]));
    } catch (const exceptions::ParsingError &error) {
        throw exceptions::ParamsError("Bad arguments");
    }
    if (_time <= 0 || _nb_cooks <= 0 || _mult < 0.0)
        throw exceptions::ParamsError("Bad arguments");
}

plazza::Shell::Shell(const int ac, const std::vector<std::string_view> &av) {
    parsing(ac, av);
    NPlazza graphic;

    while (graphic.input != 27) {
        if (graphic.opts_get == UNKNOWN)
            graphic.printStart();
        if (graphic.opts_get == ORDER)
            graphic.printOrder();
        if (graphic.opts_get == HELP)
            graphic.printHelp();
        if (graphic.opts_get == EXIT)
            break;
    }
}
