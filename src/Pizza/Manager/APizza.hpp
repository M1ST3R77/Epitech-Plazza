/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** APizza.hpp
*/

#pragma once

#include <string>

#include "IPizza.hpp"
#include "Command.hpp"

namespace plazza {
    class APizza : public IPizza {
    public:
        APizza(PizzaType type, const std::list<PizzaIngredient> &ingredients, int cook_time, PizzaSize size);

        int getTime() override;
        std::list<PizzaIngredient> getNeededIngredient() override;
        pizza_t pack() override;
        std::string unpack() override;

    private:
        std::list<PizzaIngredient> _ingredients{};
        int _cook_time{};
        PizzaSize _size{};
        PizzaType _type{};
    };
} // plazza
