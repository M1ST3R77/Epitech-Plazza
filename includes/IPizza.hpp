/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPizza.hpp
*/

#pragma once

#include <list>

namespace plazza {
    enum PizzaIngredient {

    };

    class IPizza {
    public:
        virtual ~IPizza() = default;

        virtual int getTime() = 0;
        virtual std::list<PizzaIngredient> getNeededIngredient() = 0;
    };
}
