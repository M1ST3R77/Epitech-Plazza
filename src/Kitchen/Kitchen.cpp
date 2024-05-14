/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>
#include <bits/atomic_base.h>

namespace plazza {
    Kitchen::Kitchen() {
        while (true) {
            sleep(1);
            std::cout << 1 << "yo\n";
        }
    }

    Kitchen::~Kitchen() {
        std::cout << "bye\n";
    }
} // plazza
