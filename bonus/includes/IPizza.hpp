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

    const std::unordered_map<PizzaIngredient, std::string> ingredients_name = {
        {Dough, "Dough"},
        {Tomato, "Tomato"},
        {Gruyere, "Gruyere"},
        {Ham, "Ham"},
        {Mushrooms, "Mushrooms"},
        {Steak, "Steak"},
        {EggPlant, "EggPlant"},
        {GoatCheese, "GoatCheese"},
        {ChiefLove, "ChiefLove"}
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
