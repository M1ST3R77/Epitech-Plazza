/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.hpp
*/

#pragma once

#include <memory>

#include "IPizza.hpp"
#include "../IPC/IPC.hpp"

namespace plazza {
    class Kitchen {
    public:
        Kitchen(double mult, int nb_cooks, int restock_time, std::pair<IPC, IPC> &ipcs);

        ~Kitchen();

    private:
        void cooker(double mult);
        void ingredient_filler(int restock_time);

        std::pair<IPC, IPC> &_ipcs;
        std::vector<std::shared_ptr<IPizza>> orders{};
        std::vector<std::shared_ptr<IPizza>> cooking{};
        std::mutex order_mutex{};
        std::mutex ingredients_mutex{};
        std::vector<int> nb_ingredient;
    };
} // plazza
