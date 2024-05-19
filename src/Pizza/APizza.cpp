/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** APizza.cpp
*/

#include "APizza.hpp"

namespace plazza {
    APizza::APizza(const std::list<PizzaIngredient> &ingredients, const int cook_time) : _ingredients(ingredients), _cook_time(cook_time) {
    }

    int APizza::getTime() {
        return _cook_time;
    }

    std::list<PizzaIngredient> APizza::getNeededIngredient() {
        return _ingredients;
    }
} // plazza
