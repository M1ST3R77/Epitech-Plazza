/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** PizzaPacker.hpp
*/

#pragma once

#include <string>

#include "Command.hpp"

namespace plazza {
    class PizzaPacker {
    public:
        static pizza_t pack(const std::string &order_unpacked);
        static std::string unpack(const pizza_t &order_packed);
    };
}
