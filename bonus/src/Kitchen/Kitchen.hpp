/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.hpp
*/

#pragma once

#include <chrono>
#include <memory>
#include <thread>

#include "IPizza.hpp"
#include "../IPC/IPC.hpp"

namespace plazza {
    typedef struct status_s {
        size_t orders_waiting;
        size_t orders_being_cooked;
        size_t nb_cooks;
        std::array<int, NbIngredients> ingredients;
    } kitchen_status_t;

    class Kitchen {
    public:
        Kitchen(double mult, int nb_cooks, int restock_time, std::pair<std::pair<IPC, IPC>, IPC> &ipcs);

        ~Kitchen();

    private:
        void cooker(double mult);
        void ingredient_filler(int restock_time);

        bool stop{false};
        std::chrono::system_clock::time_point end_clock;
        std::thread thread_ingr;
        std::pair<std::pair<IPC, IPC>, IPC> &_ipcs;
        std::vector<std::shared_ptr<IPizza>> orders{};
        std::vector<std::shared_ptr<IPizza>> cooking{};
        std::mutex order_mutex{};
        std::mutex ingredients_mutex{};
        std::array<int, NbIngredients> nb_ingredient;
    };
} // plazza
