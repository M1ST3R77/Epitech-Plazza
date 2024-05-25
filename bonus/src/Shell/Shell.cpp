/*
** EPITECH PROJECT, 2024
** B-CCP-400_theplazza
** File description:
** Shell.cpp
*/

#include <ranges>

#include "Main.hpp"
#include "../Graphic/NPlazza.hpp"
#include "Utils.hpp"
#include "../Logger/Logger.hpp"
#include "../Pizza/Manager/PizzaPacker.hpp"

std::pair<IPC, IPC> &plazza::Shell::getLeastBusyKitchen() {
    std::vector<std::pair<int, std::pair<IPC, IPC> &>> kitchen_cooks;
    std::list<pid_t> pid_to_erase{};
    for (auto &[pid, ipcs] : _kitchens.processes) {
        if (const pid_t result = waitpid(pid, nullptr, WNOHANG); result == 0) {
            ipcs.first.second << "nb_cooking";
            std::string msg;
            ipcs.first.first >> msg;
            kitchen_cooks.emplace_back(str_to_int(msg), ipcs.first);
        } else if (result == -1)
            throw exceptions::ProcessError(std::string("Can't check if kitchen ") + std::to_string(pid) + " is alive");
        else
            pid_to_erase.push_back(pid);
    }
    mutex_kitchens.lock();
    for (const pid_t &pid : pid_to_erase)
        _kitchens.processes.erase(pid);
    mutex_kitchens.unlock();
    auto min_cook = kitchen_cooks.begin();
    for (auto it = kitchen_cooks.begin(); it != kitchen_cooks.end(); ++it)
        if (min_cook->first > it->first)
            min_cook = it;
    if (min_cook == kitchen_cooks.end() || min_cook->first >= _nb_cooks * 2) {
        const pid_t new_pid = _kitchens.addProcess([this](std::pair<std::pair<IPC, IPC>, std::pair<IPC, IPC>> &ipcs) {
            return Kitchen(_mult, _nb_cooks, _restock_time, ipcs);
        });
        return _kitchens.processes[new_pid].first;
    }
    return min_cook->second;
}

void plazza::Shell::givePizza(const PizzaType type, const PizzaSize size) {
    auto &[kitchen_in, kitchen_out] = getLeastBusyKitchen();
    kitchen_out << std::string("new_pizza");
    std::string msg;
    kitchen_in >> msg;
    if (msg != "ready")
        throw exceptions::ProcessError("Unkown message received: " + msg);
    kitchen_out << (pizza_t){type, size};
}

std::unordered_map<pid_t, plazza::kitchen_status_t> plazza::Shell::getKitchenStatus() {
    std::unordered_map<pid_t, kitchen_status_t> kitchen_status{};
    for (auto &[pid, ipcs] : _kitchens.processes) {
        if (const pid_t result = waitpid(pid, nullptr, WNOHANG); result == 0) {
            ipcs.first.second << "status";
            kitchen_status_t status;
            ipcs.first.first >> status;
            kitchen_status.emplace(pid, status);
        }
    }
    return kitchen_status;
}

void plazza::Shell::displayKitchenStatus() {
    const std::unordered_map<pid_t, kitchen_status_t> kitchen_status = getKitchenStatus();

    if (kitchen_status.empty())
        std::cout << "All Kitchens are closed\n";
    for (const auto &[pid, status] : kitchen_status) {
        std::string str = "Kitchen ";
        str += std::to_string(pid) + ":\n" + std::to_string(status.orders_waiting) + " orders waiting to be cooked,\n" +
               std::to_string(status.orders_being_cooked) + " orders being cooked by\n" +
               std::to_string(status.nb_cooks) + " cookers working\nHere is the left ingredients :\n";
        for (size_t i = 0; i < NbIngredients; i++)
            str += " - " + std::to_string(status.ingredients[i]) + ' ' + ingredients_name.at(static_cast<PizzaIngredient>(i)) + " left\n";
        str += '\n';
        std::cout << str;
    }
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

void plazza::Shell::pizzaReceiver(NPlazza grap) {
    std::vector<std::string> pop_pizza;
    int ypos = 0;

    while (!stop) {
        mutex_kitchens.lock();
        for (auto &ipcs : _kitchens.processes | std::views::values | std::views::values) {
            if (!ipcs.first.contentWaiting())
                continue;
            std::string msg;
            ipcs.first >> msg;
            if (msg != "pizza ready")
                throw exceptions::ProcessError("Unkown message received: " + msg);
            ipcs.second << "ready";
            pizza_t order;
            ipcs.first >> order;
            std::string pizza = PizzaPacker::unpack(order);
            std::string string = std::string("Reception : Pizza ready : ") + PizzaPacker::unpack(order);
            Logger::log(std::string("Reception : Pizza ready : ") + pizza, Logger::Info);

            if (pop_pizza.size() >= 3)
                pop_pizza.pop_back();
            pop_pizza.insert(pop_pizza.begin(), pizza);

            ypos = 0;
            for (const std::string& tmp : pop_pizza) {
                grap.printString(tmp + std::string(" is ready!"), 160, 35 + ypos);
                ypos += 2;
            }
            grap.refreshWindow();

            ypos = 0;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            for (const std::string& tmp : pop_pizza) {
                grap.printEmpty(160, 35 + ypos, tmp.size() + std::string(" is ready!").size());
                ypos += 2;
            }
            grap.refreshWindow();
        }
        mutex_kitchens.unlock();
    }
}

void plazza::Shell::sendPizza(plazza::NPlazza &grap)
{
    for (const auto &[type, size, number] : grap.commands)
        for (int i = 0; i < number; i++)
            givePizza(type, size);
    grap.commands.clear();
}

plazza::Shell::Shell(const int ac, const std::vector<std::string_view> &av) {
    parsing(ac, av);
    NPlazza graphic;
    std::thread pizza_receiver([this, &graphic] { return this->pizzaReceiver(graphic); });

    while (graphic.input != 27) {
        if (graphic.opts_get == UNKNOWN)
            graphic.printStart();
        else if (graphic.opts_get == ORDER)
            graphic.printOrder();
        else if (graphic.opts_get == STATUS)
            graphic.printStatus(getKitchenStatus());
        else if (graphic.opts_get == HELP)
            graphic.printHelp();
        else if (graphic.opts_get == EXIT)
            break;
        if (graphic.send) {
            sendPizza(graphic);
            graphic.send = false;
        }
    }
    stop = true;
    pizza_receiver.join();
}
