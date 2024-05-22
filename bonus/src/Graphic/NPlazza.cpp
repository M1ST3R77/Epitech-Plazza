/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.cpp
*/

#include "NPlazza.hpp"

plazza::NPlazza::NPlazza() : NCurses(), lines(LINES), cols(COLS) {}

void plazza::NPlazza::print2D(const std::vector<std::string>& elem, int xpos, int ypos)
{
    for (const auto &tmp : elem) {
        printString(tmp, cols / 2 - tmp.length() / 2 + xpos, lines / 2 + ypos);
        ypos++;
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
    print2D(tPlazza, 0, -17);
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
    print2D(tHelp, 0, -17);
    displayHelp(*this);
    input = getInput();
    if (input == '\n')
        opts_get = UNKNOWN;
}


static void displayOrder(plazza::NPlazza grap)
{
    std::unordered_map<plazza::cOrder_enum, std::pair<int, int>> choose_order
            {
                {plazza::ORD, std::make_pair(48, -1)},
                {plazza::ADD, std::make_pair(10, 9)},
                {plazza::SEND, std::make_pair(10, 12)},
                {plazza::BACK, std::make_pair(10, 15)}
            };

    std::string dvertical(62, '_');
    std::unordered_map<plazza::cOrder_enum, std::pair<int, int>>::iterator it =
            choose_order.find(grap.opts_order);
    std::unordered_map<std::string, std::pair<int, int>> str_order
            {
                    {">", std::make_pair(-it->second.first, it->second.second)},
                    {"ORDER :", std::make_pair(-40, -1)},
                    {"TYPE", std::make_pair(-20, -6)},
                    {"SIZE", std::make_pair(0, -6)},
                    {"NUMBER", std::make_pair(18, -6)},
                    {"ADDS", std::make_pair(0, 9)},
                    {"SEND", std::make_pair(0, 12)},
                    {"BACK", std::make_pair(0, 15)}
            };
    std::vector<std::string> dhorizontal {"|", "|", "|", "|", "|", "|", "|"};

    for (const auto &tmp : str_order)
        grap.printString(tmp.first, grap.cols / 2 + tmp.second.first, grap.lines / 2 + tmp.second.second);
    grap.printString(dvertical, grap.cols / 2 - 30, grap.lines / 2 - 5);
    grap.print2D(dhorizontal, -30, -4);
    grap.print2D(dhorizontal, -7, -4);
    grap.print2D(dhorizontal, 9, -4);
    grap.print2D(dhorizontal, 31, -4);
    grap.printString(dvertical, grap.cols / 2 - 30, grap.lines / 2 + 2);
}

static void printType(plazza::NPlazza grap, plazza::PizzaType type, int pos)
{
    size_t midx = grap.cols / 2;
    size_t midy = grap.lines / 2;
    std::unordered_map<plazza::PizzaType, std::string>::iterator it;

    it = plazza::revTypes.find(type);
    grap.printString(it->second, midx - 30 + (12 - it->second.length() / 2), midy + pos);
}

static void printSize(plazza::NPlazza grap, plazza::PizzaSize size, int pos)
{
    size_t midx = grap.cols / 2;
    size_t midy = grap.lines / 2;
    std::unordered_map<plazza::PizzaSize, std::string>::iterator it;

    it = plazza::revSizes.find(size);
    grap.printString(it->second, midx - 11 + (12 - it->second.length() / 2), midy + pos);
}

static void printDigit(plazza::NPlazza grap, int digit, int col, int line)
{
    size_t midx = grap.cols / 2;
    size_t midy = grap.lines / 2;

    grap.printString(std::to_string(digit), midx + col + 12, midy + line);
}

static void printCOrder(plazza::NPlazza grap)
{
    if (grap.choose_cmd.pizza != plazza::Regina)
        printType(grap, static_cast<plazza::PizzaType>(grap.choose_cmd.pizza / 2), -3);
    if (grap.choose_cmd.pizza != plazza::Fantasia)
        printType(grap, static_cast<plazza::PizzaType>(grap.choose_cmd.pizza * 2), 1);
    if (grap.choose_cmd.size != plazza::S)
        printSize(grap, static_cast<plazza::PizzaSize>(grap.choose_cmd.size / 2), -3);
    if (grap.choose_cmd.size != plazza::XXL)
        printSize(grap, static_cast<plazza::PizzaSize>(grap.choose_cmd.size * 2), 1);
    if (grap.choose_cmd.d1 != 0)
        printDigit(grap, grap.choose_cmd.d1 - 1, 6, -3);
    if (grap.choose_cmd.d1 != 9)
        printDigit(grap, grap.choose_cmd.d1 + 1, 6, 1);
    if (grap.choose_cmd.d2 != 0)
        printDigit(grap, grap.choose_cmd.d2 - 1, 11, -3);
    if (grap.choose_cmd.d2 != 9)
        printDigit(grap, grap.choose_cmd.d2 + 1, 11, 1);
    printType(grap, grap.choose_cmd.pizza, -1);
    printSize(grap, grap.choose_cmd.size, -1);
    printDigit(grap, grap.choose_cmd.d1, 6, -1);
    printDigit(grap, grap.choose_cmd.d2, 11, -1);
}

void plazza::NPlazza::input_enter(plazza::Shell shell)
{
    if (opts_order == plazza::BACK) {
        commands.clear();
        opts_get = plazza::UNKNOWN;
    } else if (opts_order == plazza::ADD) {
        plazza::command_t tmp =
                {
                    choose_cmd.pizza,
                    choose_cmd.size,
                    choose_cmd.d1 * 10 + choose_cmd.d2
                };
        commands.push_back(tmp);
    } else if (opts_order == plazza::SEND) {
        for (const auto &[type, size, number] : commands)
            for (int i = 0; i < number; i++)
                shell.givePizza(type, size);
        commands.clear();
    }
}

static plazza::cOrder_enum input_tab(plazza::cOrder_enum opts_order)
{
    if (opts_order == plazza::BACK)
        return plazza::ORD;
    else
        return static_cast<plazza::cOrder_enum>(opts_order + 1);
}

static plazza::OType_enum input_type(int input, plazza::OType_enum order_type)
{
    if (input == KEY_LEFT && order_type != plazza::TYPE)
        return static_cast<plazza::OType_enum>(order_type - 1);
    else if (input == KEY_RIGHT && order_type != plazza::D2)
        return static_cast<plazza::OType_enum>(order_type + 1);
    else
        return order_type;
}

void plazza::NPlazza::choose_order(float mult, int numb)
{
    PizzaType limType = (mult == 0.5) ? Regina : Fantasia;
    PizzaSize limSize = (mult == 0.5) ? S : XXL;
    int limNumb = (mult == 0.5) ? 0 : 9;

    if (order_type == TYPE && choose_cmd.pizza != limType)
        choose_cmd.pizza = static_cast<PizzaType>(static_cast<float>(choose_cmd.pizza) * mult);
    if (order_type == SIZE && choose_cmd.size != limSize)
        choose_cmd.size = static_cast<PizzaSize>(static_cast<float>(choose_cmd.size) * mult);
    if (order_type == D1 && choose_cmd.d1 != limNumb)
        choose_cmd.d1 += numb;
    if (order_type == D2 && choose_cmd.d2 != limNumb)
        choose_cmd.d2 += numb;
}

void plazza::NPlazza::setInputOrder(plazza::Shell shell) {
    input = getInput();

    if (input == '\n')
        input_enter(std::move(shell));
    else if (input == '\t')
        opts_order = input_tab(opts_order);
    else if (opts_order == ORD) {
        order_type = input_type(input, order_type);
        if (input == KEY_UP)
            choose_order(0.5, -1);
        else if (input == KEY_DOWN)
            choose_order(2, 1);
    }
}

void plazza::NPlazza::printOrder(plazza::Shell shell)
{
    clearWindow();
    print2D(tOrder, 0, -17);
    displayOrder(*this);
    printCOrder(*this);
    setInputOrder(std::move(shell));
}
