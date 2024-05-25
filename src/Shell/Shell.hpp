/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.hpp
*/

#pragma once

#include "../Parsing/Parsing.hpp"
#include "../Process/ProcessPool.hpp"
#include "../Kitchen/Kitchen.hpp"

namespace plazza {
    class Shell {
    public:
        Shell(int ac, const std::vector<std::string_view> &av);
        ~Shell();

    private:
        void parsing(int ac, const std::vector<std::string_view> &av);
        static void helpParsing();
        std::pair<IPC, IPC> &getLeastBusyKitchen();
        void givePizza(PizzaType type, PizzaSize size);
        std::unordered_map<pid_t, kitchen_status_t> getKitchenStatus();
        void displayKitchenStatus();
        void pizzaReceiver();

        double _mult{};
        int _nb_cooks{};
        int _restock_time{};
        bool stop{false};
        ProcessPool _kitchens{};
        std::mutex mutex_kitchens{};
        std::thread pizza_receiver;
    };
}
