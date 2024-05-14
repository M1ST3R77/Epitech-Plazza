/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Parsing.hpp
*/

#include "Parsing.hpp"
#include "../src/Exceptions/Exceptions.hpp"
#include "Utils.hpp"

#include <utility>
#include <sstream>

void plazza::Parsing::setCmd(std::string cmd) {
    _cmd = std::move(cmd);
}

plazza::PizzaType plazza::Parsing::getPizza(const std::string &elem)
{
    std::unordered_map<std::string, PizzaType>::iterator it;

    it = types.find(str_to_lower(elem));
    if (it == types.end())
        throw exceptions::ParsingError("Bad arguments");
    return it->second;
}

plazza::PizzaSize plazza::Parsing::getSize(const std::string &elem)
{
    std::unordered_map<std::string, PizzaSize>::iterator it;

    it = sizes.find(elem);
    if (it == sizes.end())
        throw exceptions::ParsingError("Bad arguments");
    return it->second;
}

int plazza::Parsing::getNumber(const std::string &elem) {
    if (elem.length() < 2)
        throw exceptions::ParsingError("Bad arguments");
    if (elem[0] != 'x')
        throw exceptions::ParsingError("Bad arguments");
    const int number = str_to_int(elem.substr(1));
    if (number <= 0)
        throw exceptions::ParsingError("Bad arguments");
    return number;
}

plazza::command_t plazza::Parsing::getElement(const std::string &cmd) {
    int cnt_elem = 0;
    command_t final_cmd{};
    std::stringstream scmd(cmd);
    std::string elem;

    for (int i = 0; std::getline(scmd, elem, ' ');) {
        if (!elem.empty()) {
            if (cnt_elem == 3)
                throw exceptions::ParsingError("Wrong number of arguments");
            if (i == 0) {
                final_cmd.pizza = getPizza(elem);
                cnt_elem++;
            }
            if (i == 1) {
                final_cmd.size = getSize(elem);
                cnt_elem++;
            }
            if (i == 2) {
                final_cmd.number = getNumber(elem);
                cnt_elem++;
            }
            i++;
        }
    }
    if (cnt_elem != 3)
        throw exceptions::ParsingError("Wrong number of arguments");
    return final_cmd;
}

void plazza::Parsing::getCommand() {
    if (_cmd.empty())
        return;

    std::stringstream scmd(_cmd);
    std::string tmp;

    while (std::getline(scmd, tmp, ';'))
        _commands.push_back(getElement(tmp));
}
