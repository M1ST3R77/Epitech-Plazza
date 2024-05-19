/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** APizza.hpp
*/

#pragma once

#include "IPizza.hpp"

namespace plazza {
    class APizza : public IPizza {
    public:
        explicit APizza(const std::list<PizzaIngredient> &ingredients = {}, int cook_time = 0);

        int getTime() override;
        std::list<PizzaIngredient> getNeededIngredient() override;

    private:
        std::list<PizzaIngredient> _ingredients{};
        int _cook_time{};
    };
} // plazza
