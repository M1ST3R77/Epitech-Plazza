/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPizza.hpp
*/

#pragma once

#include <list>

#include "Command.hpp"

namespace plazza {
    enum PizzaIngredient {
        Dough = 0,
        Tomato,
        Gruyere,
        Ham,
        Mushrooms,
        Steak,
        EggPlant,
        GoatCheese,
        ChiefLove,
        NbIngredients
    };

    class IPizza {
    public:
        virtual ~IPizza() = default;

        virtual int getTime() = 0;
        virtual std::list<PizzaIngredient> getNeededIngredient() = 0;

        virtual pizza_t pack() = 0;
        virtual std::string unpack() = 0;
    };
}
