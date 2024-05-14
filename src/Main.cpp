/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Main.cpp
*/

#include "Main.hpp"

int main(const int ac, char const *const *av) {
    if (ac == 2 && (std::string_view(av[1]) == "--help" || std::string_view(av[1]) == "-h")) {
        std::cout << "USAGE\n\t./plazza m c t\n\nDESCRIPTION\n"
            "\tm multiplier for the cooking time of the pizzas (>= 0)\n"
            "\tc number of cooks per kitchen (> 0)\n"
            "\tt the time, in milliseconds, used by the kitchen stock to replace ingredients (> 0)\n";
        return SUCCESS_RETURN;
    }
    try {
        plazza::Shell shell(ac, std::vector<std::string_view>(av, av + ac));
    } catch (const exceptions::Error &error) {
        std::cerr << error.what() << std::endl;
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}
