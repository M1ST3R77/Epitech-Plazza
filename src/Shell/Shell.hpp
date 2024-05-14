/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.hpp
*/

#pragma once

#include <vector>

#include "../Parsing/Parsing.hpp"
#include "../Kitchen/Kitchen.hpp"

namespace plazza {
    class Shell {
    public:
        Shell(int ac, const std::vector<std::string_view> &av);

    private:
        void parsing(int ac, const std::vector<std::string_view> &av);
        static void helpParsing();

        double _mult{};
        int _nb_cooks{};
        int _time{};
        std::vector<Process<Kitchen>> _kitchens{};
    };
}
