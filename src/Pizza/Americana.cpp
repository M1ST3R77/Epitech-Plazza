/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Americana.cpp
*/

#include "Americana.hpp"

namespace plazza {
    Americana::Americana(const PizzaSize size) : APizza(PizzaType::Americana, {Dough, Tomato, Gruyere, Steak}, 2, size) {
    }
} // plazza
