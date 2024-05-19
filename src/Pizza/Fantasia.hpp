/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Fantasia.hpp
*/

#pragma once

#include "Manager/APizza.hpp"

namespace plazza {
    class Fantasia final : public APizza {
    public:
        explicit Fantasia(PizzaSize size);
    };
} // plazza
