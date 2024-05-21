/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.cpp
*/

#include "NPlazza.hpp"

plazza::NPlazza::NPlazza() : NCurses(), lines(LINES), cols(COLS) {}


void plazza::NPlazza::printTitle(plazza::opts_enum opt)
{
    int ytitle = -17;

    if (opt == UNKNOWN) {
        for (const auto &tmp : tPlazza) {
            printString(tmp, cols / 2 - tmp.length() / 2, lines / 2 + ytitle);
            ytitle++;
        }
    }
    if (opt == HELP) {
        for (const auto &tmp : tHelp) {
            printString(tmp, cols / 2 - tmp.length() / 2, lines / 2 + ytitle);
            ytitle++;
        }
    }
    if (opt == ORDER) {
        for (const auto &tmp : tOrder) {
            printString(tmp, cols / 2 - tmp.length() / 2, lines / 2 + ytitle);
            ytitle++;
        }
    }
}


static void printOpts(plazza::NPlazza grap)
{
    int ypos = -5;
    std::vector<std::string> opts = {"Order", "Details", "Help", "Exit"};

    for (const auto & opt : opts) {
        grap.printString(opt, grap.cols / 2 - opt.length() / 2, grap.lines / 2 + ypos);
        ypos += 5;
    }
}

void plazza::NPlazza::printStart()
{
    std::unordered_map<opts_enum, int>::iterator it;
    std::unordered_map<opts_enum, int> choose_opts
            {{ORDER, -5}, {DETAILS, 0}, {HELP, 5}, {EXIT, 10}};

    clearWindow();
    printTitle(opts_get);
    it = choose_opts.find(opts_choose);
    printString(">", cols / 2 - 10, lines / 2 + it->second);
    printOpts(*this);
    input = getInput();
    if ((input == KEY_UP || input == 'z') && it->second != -5)
        opts_choose = static_cast<opts_enum>(opts_choose - 1);
    if ((input == KEY_DOWN || input == 's') && it->second != 10)
        opts_choose = static_cast<opts_enum>(opts_choose + 1);
    if (input == '\n')
        opts_get = opts_choose;
}


static void displayHelp(plazza::NPlazza grap)
{
    int ypos = -2;
    std::vector<std::string> help =
            {
                    "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*",
                    "TYPE := Regina | Margarita | Americana | Fantasia",
                    "SIZE := S | M | L | XL | XXL",
                    "NUMBER := [ 1..9 ] [ 0..9 ]"
            };

    grap.printString(">", grap.cols / 2 - 10, grap.lines / 2 + 9);
    grap.printString("BACK", grap.cols / 2 - 2, grap.lines / 2 + 9);
    for (const auto & tmp : help) {
        grap.printString(tmp, grap.cols / 2 - tmp.length() / 2, grap.lines / 2 + ypos);
        ypos += 2;
    }
}

void plazza::NPlazza::printHelp()
{
    clearWindow();
    printTitle(opts_get);
    displayHelp(*this);
    input = getInput();
    if (input == '\n')
        opts_get = UNKNOWN;
}


static void displayOrder(plazza::NPlazza grap)
{
    std::unordered_map<plazza::cOrder_enum, std::pair<int, int>>::iterator it;
    std::unordered_map<plazza::cOrder_enum, std::pair<int, int>> choose_order
            {
                {plazza::ORD, std::make_pair(48, -1)},
                {plazza::ADD, std::make_pair(10, 9)},
                {plazza::SEND, std::make_pair(10, 12)},
                {plazza::BACK, std::make_pair(10, 15)}
            };

    it = choose_order.find(grap.opts_order);
    grap.printString(">", grap.cols / 2 - it->second.first, grap.lines / 2 + it->second.second);
    grap.printString("ORDER :", grap.cols / 2 - 40, grap.lines / 2 - 1);
    grap.printString("ADDS", grap.cols / 2 - 2, grap.lines / 2 + 9);
    grap.printString("SEND", grap.cols / 2 - 2, grap.lines / 2 + 12);
    grap.printString("BACK", grap.cols / 2 - 2, grap.lines / 2 + 15);
}

static void printCOrder(plazza::NPlazza grap)
{
    std::unordered_map<plazza::PizzaType, std::string>::iterator it;

    if (grap.choose_cmd.pizza != plazza::Regina) {
        it = plazza::revTypes.find(static_cast<plazza::PizzaType>(grap.choose_cmd.pizza / 2));
        grap.printString(it->second, grap.cols / 2 - 30 + (12 - it->second.length() / 2), grap.lines / 2 - 3);
    }
    if (grap.choose_cmd.pizza != plazza::Fantasia) {
        it = plazza::revTypes.find(static_cast<plazza::PizzaType>(grap.choose_cmd.pizza * 2));
        grap.printString(it->second, grap.cols / 2 - 30 + (12 - it->second.length() / 2), grap.lines / 2 + 1);
    }
    it = plazza::revTypes.find(grap.choose_cmd.pizza);
    grap.printString(it->second, grap.cols / 2 - 30 + (12 - it->second.length() / 2), grap.lines / 2 - 1);
}

void plazza::NPlazza::setInputOrder(plazza::Shell shell) {
    input = getInput();

    if (opts_order == BACK && input == '\n') {
        commands.clear();
        opts_get = UNKNOWN;
    }
    if (opts_order == ADD && input == '\n') {
        command_t tmp = {choose_cmd.pizza, choose_cmd.size, choose_cmd.d1 * 10 + choose_cmd.d2};
        commands.push_back(tmp);
    }
    if (opts_order == SEND && input == '\n') {
        for (const auto &[type, size, number] : commands)
            for (int i = 0; i < number; i++)
                shell.givePizza(type, size);
        commands.clear();
    }
    if (input == '\t' && opts_order == BACK)
        opts_order = ORD;
    else if (input == '\t')
        opts_order = static_cast<cOrder_enum>(opts_order + 1);
    else {
        if (opts_order == ORD) {
            if (input == KEY_LEFT && order_type != TYPE)
                order_type = static_cast<OType_enum>(order_type - 1);
            if (input == KEY_RIGHT && order_type != D2)
                order_type = static_cast<OType_enum>(order_type + 1);
            if (input == KEY_UP) {
                if (order_type == TYPE && choose_cmd.pizza != Regina)
                    choose_cmd.pizza = static_cast<PizzaType>(choose_cmd.pizza / 2);
            }
            if (input == KEY_DOWN) {
                if (order_type == TYPE && choose_cmd.pizza != Fantasia)
                    choose_cmd.pizza = static_cast<PizzaType>(choose_cmd.pizza * 2);
            }
        }
    }
}

void plazza::NPlazza::printOrder(plazza::Shell shell)
{
    clearWindow();
    printTitle(opts_get);
    displayOrder(*this);
    printCOrder(*this);
    setInputOrder(std::move(shell));
}
