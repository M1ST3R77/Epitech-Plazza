/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Kitchen.cpp
*/

#include "Kitchen.hpp"
#include "Command.hpp"
#include "../Logger/Logger.hpp"
#include "../Pizza/Manager/PizzaFactory.hpp"
#include "../Pizza/Manager/PizzaPacker.hpp"
#include "../ThreadPool/ThreadPool.hpp"

namespace plazza {
    Kitchen::Kitchen(const double mult, const int nb_cooks, const int restock_time, std::pair<IPC, IPC> &ipcs) :
        _ipcs(ipcs), nb_ingredient(NbIngredients, 5) {
        ThreadPool thread_pool(std::max(static_cast<unsigned>(nb_cooks) + 1, std::thread::hardware_concurrency()));
        thread_pool.enqueue([this, restock_time] { return ingredient_filler(restock_time); });
        while (true) {
            std::string msg;
            _ipcs.second >> msg;
            if (msg == "nb_cooking")
                _ipcs.first << std::to_string(orders.size() + cooking.size());
            if (msg == "new_pizza") {
                _ipcs.first << "ready";
                pizza_t order = {};
                _ipcs.second >> order;
                Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + " received pizza: " + PizzaPacker::unpack(order), Logger::Info);
                order_mutex.lock();
                orders.push_back(PizzaFactory::createPizza(order));
                order_mutex.unlock();
                thread_pool.enqueue([this, mult] { return cooker(mult); });
            }
        }
    }

    Kitchen::~Kitchen() {
        _ipcs.first.destruct();
        _ipcs.second.destruct();
    }

    void Kitchen::cooker(const double mult) {
        order_mutex.lock();
        const std::shared_ptr<IPizza> order = orders.front();
        orders.erase(orders.begin());
        cooking.push_back(order);
        order_mutex.unlock();
        const std::list<PizzaIngredient> needed_ingredients = order->getNeededIngredient();
        ingredients_mutex.lock();
        for (const auto &ingr : needed_ingredients) {
            if (nb_ingredient[ingr]) {
                nb_ingredient[ingr]--;
            } else {
                ingredients_mutex.unlock();
                while (!nb_ingredient[ingr]) {
                }
                nb_ingredient[ingr]--;
                ingredients_mutex.lock();
            }
        }
        ingredients_mutex.unlock();
        usleep(static_cast<unsigned>(mult * static_cast<double>(order->getTime()) * 1000000.0));
        Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + " successfully cooked pizza: " + order->unpack(), Logger::Info);
        order_mutex.lock();
        cooking.erase(std::ranges::find(cooking, order));
        order_mutex.unlock();
    }

    void Kitchen::ingredient_filler(const int restock_time) {
        while (true) {
            usleep(restock_time * 1000);
            ingredients_mutex.lock();
            for (auto &ingr : nb_ingredient)
                ingr += ingr != 5;
            ingredients_mutex.unlock();
        }
    }
} // plazza
