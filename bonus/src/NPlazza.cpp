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

void plazza::NPlazza::printOpts()
{
    int ypos = -5;
    std::vector<std::string> opts = {"Order", "Details", "Help", "Exit"};

    for (const auto & opt : opts) {
        printString(opt, cols / 2 - opt.length() / 2, lines / 2 + ypos);
        ypos += 5;
    }
}

void plazza::NPlazza::displayHelp()
{
    int ypos = -2;
    std::vector<std::string> help =
            {
                    "S := TYPE SIZE NUMBER [; TYPE SIZE NUMBER]*",
                    "TYPE := Regina | Margarita | Americana | Fantasia",
                    "SIZE := S | M | L | XL | XXL",
                    "NUMBER := [ 1..9 ] [ 0..9 ]"
            };

    printString(">", cols / 2 - 10, lines / 2 + 9);
    printString("BACK", cols / 2 - 2, lines / 2 + 9);
    for (const auto & tmp : help) {
        printString(tmp, cols / 2 - tmp.length() / 2, lines / 2 + ypos);
        ypos += 2;
    }
}

void plazza::NPlazza::displayOrder()
{
    std::unordered_map<cOrder_enum, std::pair<int, int>>::iterator it;
    std::unordered_map<cOrder_enum, std::pair<int, int>> choose_order
            {
                {ORD, std::make_pair(38, -1)},
                {ADD, std::make_pair(10, 9)},
                {SEND, std::make_pair(10, 12)},
                {BACK, std::make_pair(10, 15)}
            };

    it = choose_order.find(opts_order);
    printString(">", cols / 2 - it->second.first, lines / 2 + it->second.second);
    printString("ORDER :", cols / 2 - 30, lines / 2 - 1);
    printString("ADDS", cols / 2 - 2, lines / 2 + 9);
    printString("SEND", cols / 2 - 2, lines / 2 + 12);
    printString("BACK", cols / 2 - 2, lines / 2 + 15);
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
    printOpts();
    input = getInput();
    if ((input == KEY_UP || input == 'z') && it->second != -5)
        opts_choose = static_cast<opts_enum>(opts_choose - 1);
    if ((input == KEY_DOWN || input == 's') && it->second != 10)
        opts_choose = static_cast<opts_enum>(opts_choose + 1);
    if (input == '\n')
        opts_get = opts_choose;
}

void plazza::NPlazza::printHelp()
{
    clearWindow();
    printTitle(opts_get);
    displayHelp();
    input = getInput();
    if (input == '\n')
        opts_get = UNKNOWN;
}

void plazza::NPlazza::printOrder()
{
    clearWindow();
    printTitle(opts_get);
    displayOrder();
    input = getInput();
    if (input == '\t' && opts_order == BACK)
        opts_order = ORD;
    else if (input == '\t')
        opts_order = static_cast<cOrder_enum>(opts_order + 1);
    if (opts_order == BACK && input == '\n')
        opts_get = UNKNOWN;
}
