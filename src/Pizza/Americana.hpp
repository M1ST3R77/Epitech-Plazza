/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Americana.hpp
*/

#pragma once

#include "Manager/APizza.hpp"

namespace plazza {
    class Americana final : public APizza {
    public:
        explicit Americana(PizzaSize size);
    };
} // plazza
