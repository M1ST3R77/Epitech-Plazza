/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Utils.cpp
*/

#include <stdexcept>
#include <algorithm>

#include "Utils.hpp"

static bool str_isint(const std::string &str)
{
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}

static bool str_isfloat(const std::string &str)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] != '.' && !isdigit(str[i]))
            return false;
    }
    return true;
}

int str_to_int(const std::string &str)
{
    int number;

    if (!str_isint(str))
        throw exceptions::ParsingError("Bad arguments");
    try {
        number = std::stoi(str);
    } catch (const std::invalid_argument &) {
        throw exceptions::ParsingError("Bad arguments");
    } catch (const std::out_of_range &) {
        throw exceptions::ParsingError("Bad arguments");
    }
    return number;
}

float str_to_float(const std::string &str)
{
    float number;

    if (!str_isfloat(str))
        throw exceptions::ParsingError("Bad arguments");
    try {
        number = std::stof(str);
    } catch (const std::invalid_argument &) {
        throw exceptions::ParsingError("Bad arguments");
    } catch (const std::out_of_range &) {
        throw exceptions::ParsingError("Bad arguments");
    }
    return number;
}

std::string str_to_lower(const std::string &str)
{
    std::string res = str;

    std::transform(res.begin(), res.end(), res.begin(),[](unsigned char c){
        return std::tolower(c);
    });
    return res;
}
