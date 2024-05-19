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
        const std::string _error;
    };

    class ParamsError final : public Error {
    public:
        explicit ParamsError(const std::string &error);
    };

    class ParsingError final : public Error {
    public:
        explicit ParsingError(const std::string &error);
    };

    class ProcessError final : public Error {
    public:
        explicit ProcessError(const std::string &error);
    };
}
