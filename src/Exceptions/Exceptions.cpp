/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Exception.cpp
*/

#include "Exceptions.hpp"

exceptions::Error::Error(const std::string &error) :
    _error("plazza: " + error) {
}

const char *exceptions::Error::what() const noexcept {
    return this->_error.c_str();
}

exceptions::ParamsError::ParamsError(const std::string &error) :
    Error(error + " ! Use \"plazza --help\" for more informations.") {
}

exceptions::ParsingError::ParsingError(const std::string &error) :
    Error(error + " ! Use \"help\" in interactive shell for more informations.") {
}

exceptions::ProcessError::ProcessError(const std::string &error) :
    Error("Can't proceed with kitchens : " + error) {
}
