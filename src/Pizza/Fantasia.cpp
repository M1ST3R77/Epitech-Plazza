/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Fantasia.cpp
*/

#include "Fantasia.hpp"

namespace plazza {
    Fantasia::Fantasia(const PizzaSize size) : APizza(PizzaType::Fantasia, {Dough, Tomato, EggPlant, GoatCheese, ChiefLove}, 4, size) {
    }
} // plazza
