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
            explicit Error(const std::string &error) :
                _Error("plazza: " + error) {}
            [[nodiscard]] const char *what() const noexcept override
            {
                return this->_Error.c_str();
            }
        private:
            const std::string _Error;
    };
    class ParamsError : public Error {
        public:
            explicit ParamsError(const std::string &error) :
                Error(error + " ! Use \"plazza --help\" for more informations.") {}
    };
}