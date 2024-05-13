/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** main.cpp
*/

#include <iostream>

#include "Shell.hpp"
#include "Exceptions.hpp"
#include "define.hpp"

int main(int ac, char const *const *av)
{
    try {
        plazza::Shell shell(ac, std::vector<std::string_view>(av, av + ac));
    } catch (const exceptions::Error &error) {
        std::cerr << error.what() << std::endl;
        return ERROR_RETURN;
    }
    return SUCCESS_RETURN;
}