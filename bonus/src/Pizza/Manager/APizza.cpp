/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** APizza.cpp
*/

#include "APizza.hpp"

#include "PizzaPacker.hpp"

namespace plazza {
    APizza::APizza(const PizzaType type, const std::list<PizzaIngredient> &ingredients, const int cook_time, const PizzaSize size) :
        _ingredients(ingredients), _cook_time(cook_time), _size(size), _type(type) {
    }

    int APizza::getTime() {
        return _cook_time;
    }

    std::list<PizzaIngredient> APizza::getNeededIngredient() {
        return _ingredients;
    }

    pizza_t APizza::pack() {
        return (pizza_t){_type, _size};
    }

    std::string APizza::unpack() {
        return PizzaPacker::unpack({_type, _size});
    }
} // plazza
