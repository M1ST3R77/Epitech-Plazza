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

#include "Margarita.hpp"
#include "Regina.hpp"
#include "Americana.hpp"
#include "Fantasia.hpp"

namespace plazza {
    class PizzaFactory {
    public:
        static std::unique_ptr<IPizza> createPizza(const std::string &name);

    private:
        inline static std::unordered_map<std::string, std::unique_ptr<IPizza> (*)()> const _ctor = {
            std::make_pair("margarita", []() -> std::unique_ptr<IPizza> { return std::make_unique<class Margarita>(); }),
            std::make_pair("regina", []() -> std::unique_ptr<IPizza> { return std::make_unique<class Regina>(); }),
            std::make_pair("americana", []() -> std::unique_ptr<IPizza> { return std::make_unique<class Americana>(); }),
            std::make_pair("fantasia", []() -> std::unique_ptr<IPizza> { return std::make_unique<class Fantasia>(); })
        };
    };
}
