/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Margarita.cpp
*/

#include "Margarita.hpp"

namespace plazza {
    Margarita::Margarita(const PizzaSize size) : APizza(PizzaType::Margarita, {Dough, Tomato, Gruyere}, 1, size) {
    }
} // plazza
