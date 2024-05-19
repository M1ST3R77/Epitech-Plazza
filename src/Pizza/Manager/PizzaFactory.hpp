/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** PizzaFactory.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "IPizza.hpp"

#include "../Margarita.hpp"
#include "../Regina.hpp"
#include "../Americana.hpp"
#include "../Fantasia.hpp"

namespace plazza {
    class PizzaFactory {
    public:
        static std::unique_ptr<IPizza> createPizza(const std::string &name, const std::string &size);
        static std::unique_ptr<IPizza> createPizza(const pizza_t &pizza);

    private:
        inline static std::unordered_map<PizzaType, std::unique_ptr<IPizza> (*)(PizzaSize size)> const _ctor = {
            std::make_pair(Margarita, [](const PizzaSize size) -> std::unique_ptr<IPizza> { return std::make_unique<class Margarita>(size); }),
            std::make_pair(Regina, [](const PizzaSize size) -> std::unique_ptr<IPizza> { return std::make_unique<class Regina>(size); }),
            std::make_pair(Americana, [](const PizzaSize size) -> std::unique_ptr<IPizza> { return std::make_unique<class Americana>(size); }),
            std::make_pair(Fantasia, [](const PizzaSize size) -> std::unique_ptr<IPizza> { return std::make_unique<class Fantasia>(size); })
        };
    };
}
