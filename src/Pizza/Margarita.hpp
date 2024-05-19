/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Margarita.hpp
*/

#pragma once

#include "Manager/APizza.hpp"

namespace plazza {
    class Margarita final : public APizza {
    public:
        explicit Margarita(PizzaSize size);
    };
} // plazza
