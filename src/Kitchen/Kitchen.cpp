/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>

namespace plazza {
    Kitchen::Kitchen(const double mult, const int nb_cooks, const int restock_time, std::pair<IPC, IPC> &ipcs) :
        _ipcs(ipcs), _nb_cooks(0) {
        while (true) {
            std::string msg;
            _ipcs.second >> msg;
            if (msg == "nb_cooking")
                _ipcs.first << std::to_string(_nb_cooks);
            if (msg == "new_pizza") {
                _ipcs.first << "ready";
                _ipcs.second >> msg;
                _nb_cooks++;
                std::cout << msg << std::endl;
            }
        }
    }

    Kitchen::~Kitchen() {
        _ipcs.first.destruct();
        _ipcs.second.destruct();
    }
} // plazza
