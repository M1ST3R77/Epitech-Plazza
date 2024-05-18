/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Parsing.hpp
*/

#pragma once

#include <vector>
#include <string>

#include "Command.hpp"

namespace plazza {
    class Parsing {
    public:
        void getCommand();
        [[nodiscard]] static command_t getElement(const std::string &cmd);
        static PizzaType getPizza(const std::string &elem);
        static PizzaSize getSize(const std::string &elem);
        static int getNumber(const std::string &elem);
        void setCmd(std::string cmd);

        std::vector<command_t> _commands;

    private:
        std::string _cmd;
    };
}
