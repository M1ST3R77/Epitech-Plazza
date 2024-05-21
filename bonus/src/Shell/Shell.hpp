/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.hpp
*/

#pragma once

#include "Command.hpp"
#include "../Process/ProcessPool.hpp"

namespace plazza {
    class Shell {
    public:
        Shell(int ac, const std::vector<std::string_view> &av);
        void givePizza(PizzaType type, PizzaSize size);

    private:
        void parsing(int ac, const std::vector<std::string_view> &av);
        static void helpParsing();
        std::pair<IPC, IPC> &getLeastBusyKitchen();

        double _mult{};
        int _nb_cooks{};
        int _restock_time{};
        ProcessPool _kitchens{};
    };
}
