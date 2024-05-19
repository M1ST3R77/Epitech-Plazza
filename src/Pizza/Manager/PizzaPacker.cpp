/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** PizzaPacker.cpp
*/

#include "PizzaPacker.hpp"

namespace plazza {
    pizza_t PizzaPacker::pack(const std::string &order_unpacked) {
        return {
            types[order_unpacked.substr(0, order_unpacked.find(' '))],
            sizes[order_unpacked.substr(order_unpacked.find(' ') + 1, order_unpacked.size())]
        };
    }

    std::string PizzaPacker::unpack(const pizza_t &order_packed) {
        return revTypes[order_packed.pizza] + " " + revSizes[order_packed.size];
    }
}
