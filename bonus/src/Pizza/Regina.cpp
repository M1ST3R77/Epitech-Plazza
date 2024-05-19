/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Regina.cpp
*/

#include "Regina.hpp"

namespace plazza {
    Regina::Regina(const PizzaSize size) : APizza(PizzaType::Regina, {Dough, Tomato, Gruyere, Ham, Mushrooms}, 2, size) {
    }
} // plazza
