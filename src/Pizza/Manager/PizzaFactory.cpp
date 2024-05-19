/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** PizzaFactory.cpp
*/

#include "PizzaFactory.hpp"

#include "../../Exceptions/Exceptions.hpp"

namespace plazza {
    std::unique_ptr<IPizza> PizzaFactory::createPizza(const std::string &name, const std::string &size) {
        if (!_ctor.contains(types.at(name)))
            throw exceptions::ParsingError("Pizza " + name + " don't exist");
        return _ctor.at(types.at(name))(sizes.at(size));
    }

    std::unique_ptr<IPizza> PizzaFactory::createPizza(const pizza_t &pizza) {
        if (!_ctor.contains(pizza.pizza))
            throw exceptions::ParsingError("Pizza " + revTypes.at(pizza.pizza) + " don't exist");
        return _ctor.at(pizza.pizza)(pizza.size);
    }
}
