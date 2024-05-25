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
    Kitchen::Kitchen(const double mult, const int nb_cooks, const int restock_time, std::pair<std::pair<IPC, IPC>, IPC> &ipcs) :
        _ipcs(ipcs), nb_ingredient() {
        end_clock = std::chrono::system_clock::now();
        for (auto &ingr : nb_ingredient)
            ingr = 5;
        ThreadPool thread_pool(std::max(static_cast<unsigned>(nb_cooks), std::thread::hardware_concurrency()));
        thread_ingr = std::thread([this, restock_time] { return ingredient_filler(restock_time); });

        Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + ": Started", Logger::Info);

        while (!stop) {
            std::string msg;
            while (!_ipcs.first.second.contentWaiting()) {
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                if (!cooking.empty() || !orders.empty()) {
                    end_clock = now;
                    continue;
                }
                if (std::chrono::duration<double> elapsed_seconds = now - end_clock; elapsed_seconds.count() >= 5.0) {
                    stop = true;
                    return;
                }
            }
            _ipcs.first.second >> msg;
            if (msg == "status") {
                order_mutex.lock();
                ingredients_mutex.lock();
                _ipcs.first.first << (kitchen_status_t){orders.size(), cooking.size(), thread_pool.activeThreads, nb_ingredient};
                ingredients_mutex.unlock();
                order_mutex.unlock();
                continue;
            }
            end_clock = std::chrono::system_clock::now();
            if (msg == "nb_cooking")
                _ipcs.first.first << std::to_string(orders.size() + cooking.size());
            if (msg == "new_pizza") {
                _ipcs.first.first << "ready";
                pizza_t order = {};
                _ipcs.first.second >> order;
                Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + " received pizza: " + PizzaPacker::unpack(order), Logger::Info);
                order_mutex.lock();
                orders.push_back(PizzaFactory::createPizza(order));
                order_mutex.unlock();
                thread_pool.enqueue([this, mult] { return cooker(mult); });
            }
        }
    }

    Kitchen::~Kitchen() {
        Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + ": Stopped", Logger::Info);
        thread_ingr.join();
    }

    void Kitchen::cooker(const double mult) {
        const std::chrono::system_clock::time_point cook_clock = std::chrono::system_clock::now();
        order_mutex.lock();
        const std::shared_ptr<IPizza> order = orders.front();
        orders.erase(orders.begin());
        cooking.push_back(order);
        order_mutex.unlock();
        const std::list<PizzaIngredient> needed_ingredients = order->getNeededIngredient();
        ingredients_mutex.lock();
        for (const auto &ingr : needed_ingredients) {
            if (nb_ingredient[ingr] > 0) {
                nb_ingredient[ingr]--;
            } else {
                ingredients_mutex.unlock();
                while (nb_ingredient[ingr] <= 0);
                nb_ingredient[ingr]--;
                ingredients_mutex.lock();
            }
        }
        ingredients_mutex.unlock();

        const double cook_time_seconde = mult * static_cast<double>(order->getTime());
        std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = now - cook_clock;
        while (elapsed_seconds.count() < cook_time_seconde) {
            now = std::chrono::system_clock::now();
            elapsed_seconds = now - cook_clock;
        }

        Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + " successfully cooked pizza: " + order->unpack(), Logger::Info);

        order_mutex.lock();
        cooking.erase(std::ranges::find(cooking, order));
        order_mutex.unlock();
        _ipcs.second << order->pack();
    }

    void Kitchen::ingredient_filler(const int restock_time) {
        std::chrono::system_clock::time_point restock_clock = std::chrono::system_clock::now();

        while (!stop) {
            const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
            if (const std::chrono::duration<double> elapsed_seconds = now - restock_clock; elapsed_seconds.count() < restock_time / 1000.0)
                continue;

            restock_clock = now;
            ingredients_mutex.lock();
            for (auto &ingr : nb_ingredient)
                ingr += ingr != 5;
            Logger::log(std::string("Kitchen ") + std::to_string(getpid()) + ": Refilled !", Logger::Info);
            ingredients_mutex.unlock();
        }
    }
} // plazza
