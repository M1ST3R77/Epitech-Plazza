/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Regina.hpp
*/

#pragma once

#include "Manager/APizza.hpp"

namespace plazza {
    class Regina final : public APizza {
    public:
        explicit Regina(PizzaSize size);
    };
} // plazza
