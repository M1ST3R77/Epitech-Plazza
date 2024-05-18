/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include <ranges>

#include "Main.hpp"
#include "../src/Parsing/Parsing.hpp"
#include "Utils.hpp"
#include "../IPC/IPC.hpp"
#include "../Kitchen/Kitchen.hpp"

void plazza::Shell::helpParsing() {
    std::cout << "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*\n"
        "TYPE := [a..zA..Z]+\n"
        "SIZE := S|M|L|XL|XXL\n"
        "NUMBER := x[1..9][0..9]*\n";
}

std::pair<IPC, IPC> &plazza::Shell::getLeastBusyKitchen() {
    std::vector<std::pair<int, std::pair<IPC, IPC> &>> kitchen_cooks;
    for (auto &[pid, ipcs] : _kitchens.processes) {
        const pid_t result = waitpid(pid, nullptr, WNOHANG);
        if (result == 0) {
            ipcs.second << "nb_cooking";
            std::string msg;
            ipcs.first >> msg;
            kitchen_cooks.emplace_back(str_to_int(msg), ipcs);
        } else if (result == -1)
            throw exceptions::ProcessError(std::string("Can't check if kitchen ") + std::to_string(pid) + " is alive");
        else
            _kitchens.processes.erase(pid);
    }
    auto min_cook = kitchen_cooks.begin();
    for (auto it = kitchen_cooks.begin(); it != kitchen_cooks.end(); ++it)
        if (min_cook->first > it->first)
            min_cook = it;
    if (min_cook == kitchen_cooks.end() || min_cook->first >= _nb_cooks * 2) {
        const pid_t new_pid = _kitchens.addProcess([this](std::pair<IPC, IPC> &ipcs) { return Kitchen(_mult, _nb_cooks, _restock_time, ipcs); });
        return _kitchens.processes[new_pid];
    }
    return min_cook->second;
}

void plazza::Shell::givePizza(PizzaType type, PizzaSize size) {
    auto &[kitchen_in, kitchen_out] = getLeastBusyKitchen();
    kitchen_out << std::string("new_pizza");
    std::string msg;
    kitchen_in >> msg;
    if (msg != "ready")
        throw exceptions::ProcessError("Unkown message received: " + msg);
    kitchen_out << revTypes[type] + ' ' + revSizes[size];
}

void plazza::Shell::parsing(const int ac, const std::vector<std::string_view> &av) {
    if (ac != 4)
        throw exceptions::ParamsError(ac < 4 ? "Not enough parameters" : "Too many parameters");
    try {
        _mult = str_to_float(std::string(av[1]));
        _nb_cooks = str_to_int(std::string(av[2]));
        _restock_time = str_to_int(std::string(av[3]));
    } catch (const exceptions::ParsingError &) {
        throw exceptions::ParamsError("Bad arguments");
    }
    if (_restock_time <= 0 || _nb_cooks <= 0 || _mult < 0.0)
        throw exceptions::ParamsError("Bad arguments");
}


plazza::Shell::Shell(const int ac, const std::vector<std::string_view> &av) {
    parsing(ac, av);
    std::string cmd;
    Parsing parse;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, cmd))
            break;
        if (cmd == "exit")
            break;
        if (cmd == "help") {
            helpParsing();
            continue;
        }
        try {
            parse.setCmd(cmd);
            parse.getCommand();
        } catch (const exceptions::ParsingError &) {
            std::cout << "Invalid Command" << std::endl;
        }
        for (const auto &[type, size, number] : parse._commands)
            for (int i = 0; i < number; i++)
                givePizza(type, size);
        parse._commands.clear();
    }
}
