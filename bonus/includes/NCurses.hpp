/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NCurses.hpp
*/

#pragma once

#include <ncurses.h>
#include <string>

namespace plazza {

    class NCurses {
        public:
            NCurses();
            ~NCurses();

            void clearWindow();
            void refreshWindow();
            int getInput();
            void printString(const std::string& str, int x, int y);
    };
}