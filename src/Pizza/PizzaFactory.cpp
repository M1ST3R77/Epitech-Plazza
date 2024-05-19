/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** PizzaFactory.cpp
*/

#include "PizzaFactory.hpp"

#include <algorithm>

#include "../Exceptions/Exceptions.hpp"

namespace plazza {
    std::unique_ptr<IPizza> PizzaFactory::createPizza(const std::string &name) {
        std::string lower = name;
        std::ranges::transform(lower, lower.begin(), [](const char c) { return std::tolower(c); });

        if (!_ctor.contains(lower))
            throw exceptions::ParsingError("Pizza " + lower + " don't exist");
        return _ctor.at(lower)();
    }
}
