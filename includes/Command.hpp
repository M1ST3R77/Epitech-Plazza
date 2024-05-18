/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Command.hpp
*/

#pragma once

#include <unordered_map>

namespace plazza {
    enum PizzaType {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8
    };

    enum PizzaSize {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16
    };

    inline std::unordered_map<std::string, PizzaSize> sizes
        {{"S", S}, {"M", M},
         {"L", L}, {"XL", XL}, {"XXL", XXL}};

    inline std::unordered_map<PizzaSize, std::string> revSizes
            {{S, "S"}, {M, "M"},
             {L, "L"}, {XL, "XL"}, {XXL, "XXL"}};


    inline std::unordered_map<std::string, PizzaType> types
        {{"regina", Regina}, {"margarita", Margarita},
         {"americana", Americana}, {"fantasia", Fantasia}};

    inline std::unordered_map<PizzaType, std::string> revTypes
            {{Regina, "regina"}, {Margarita, "margarita"},
             {Americana, "americana"}, {Fantasia, "fantasia"}};

    typedef struct command_s {
        PizzaType pizza;
        PizzaSize size;
        int number;
    } command_t;
}
