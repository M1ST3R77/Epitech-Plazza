/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.hpp
*/

#pragma once

namespace plazza {

    class Shell {
        public:
            Shell(int ac, char **av);
            void parsing(int ac, char **av);
            void help(void);
        private:
            float _Mult;
            int _NbCooks;
            int _Time;
    };
}