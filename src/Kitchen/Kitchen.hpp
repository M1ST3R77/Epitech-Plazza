/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.hpp
*/

#pragma once

#include "../IPC/IPC.hpp"

namespace plazza {
    class Kitchen {
    public:
        Kitchen(double mult, int nb_cooks, int restock_time, std::pair<IPC, IPC> &ipcs);

        ~Kitchen();

        std::pair<IPC, IPC> &_ipcs;
        int _nb_cooks;
    };
} // plazza
