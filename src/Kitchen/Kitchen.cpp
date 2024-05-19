/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"

#include <iostream>

#include "Command.hpp"
#include "../Pizza/PizzaFactory.hpp"

namespace plazza {
    Kitchen::Kitchen(const double mult, const int nb_cooks, const int restock_time, std::pair<IPC, IPC> &ipcs) :
        _ipcs(ipcs), _nb_cooks(0) {
        while (true) {
            std::string msg;
            _ipcs.second >> msg;
            if (msg == "nb_cooking")
                _ipcs.first << std::to_string(orders.size());
            if (msg == "new_pizza") {
                _ipcs.first << "ready";
                pizza_t order = {};
                _ipcs.second >> order;
                orders.push_back(PizzaFactory::createPizza(msg.substr(0, msg.find(' '))));
            }
        }
    }

    Kitchen::~Kitchen() {
        _ipcs.first.destruct();
        _ipcs.second.destruct();
    }
} // plazza
