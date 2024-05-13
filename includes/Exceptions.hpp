/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Exception.hpp
*/

#pragma once

#include <exception>
#include <string>

namespace exceptions {

    class Error : public std::exception {
        public:
            explicit Error(const std::string &error);
            [[nodiscard]] const char *what() const noexcept override;
        private:
            const std::string _Error;
    };
    class ParamsError : public Error {
        public:
            explicit ParamsError(const std::string &error);
    };
}