/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.hpp
*/

#pragma once

#include <vector>

namespace plazza {

    class Shell {
        public:
            Shell(int ac, std::vector<std::string_view> av);
            void parsing(int ac, std::vector<std::string_view> av);
            void help(void);
            void help_parsing();
        private:
            float _Mult;
            int _NbCooks;
            int _Time;
    };
}