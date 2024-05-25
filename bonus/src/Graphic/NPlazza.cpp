/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.cpp
*/

#include "NPlazza.hpp"

#include <utility>

plazza::NPlazza::NPlazza() : NCurses(), lines(LINES), cols(COLS) {}

void plazza::NPlazza::print2D(const std::vector<std::string>& elem, int xpos, int ypos, config_enum conf)
{
    for (const auto &tmp : elem) {
        if (conf == NORMAL)
            printString(tmp, cols / 2 - tmp.length() / 2 + xpos, lines / 2 + ypos);
        else if (conf == BOLD)
            printBold(tmp, cols / 2 - tmp.length() / 2 + xpos, lines / 2 + ypos);
        else
            printDim(tmp, cols / 2 - tmp.length() / 2 + xpos, lines / 2 + ypos);
        ypos++;
    }
}


static void printOpts(plazza::NPlazza grap)
{
    int ypos = -5;
    std::vector<std::string> opts = {"Order", "Status", "Help", "Exit"};

    for (const auto & opt : opts) {
        grap.printString(opt, grap.cols / 2 - opt.length() / 2, grap.lines / 2 + ypos);
        ypos += 5;
    }
}

void plazza::NPlazza::printStart()
{
    std::unordered_map<opts_enum, int>::iterator it;
    std::unordered_map<opts_enum, int> choose_opts
            {{ORDER, -5}, {STATUS, 0}, {HELP, 5}, {EXIT, 10}};

    clearWindow();
    print2D(tPlazza, 0, -17, NORMAL);
    it = choose_opts.find(opts_choose);
    printString(">", cols / 2 - 10, lines / 2 + it->second);
    printOpts(*this);
    refreshWindow();
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
    print2D(tHelp, 0, -17, NORMAL);
    displayHelp(*this);
    refreshWindow();
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

    std::unordered_map<plazza::OType_enum, std::string> choose_pizza
            {
                {plazza::TYPE, "TYPE"},
                {plazza::SIZE, "SIZE"},
                {plazza::D1, "NUMBER"},
                {plazza::D2, "NUMBER"}
            };
    std::unordered_map<plazza::OType_enum, std::string>::iterator choose;

    std::string dvertical(62, '_');
    std::unordered_map<plazza::cOrder_enum, std::pair<int, int>>::iterator it =
            choose_order.find(grap.opts_order);
    std::unordered_map<std::string, std::pair<int, int>> str_order
            {
                    {">", std::make_pair(-it->second.first, it->second.second)},
                    {"ORDER :", std::make_pair(-40, -1)},
                    {"ADDS", std::make_pair(0, 9)},
                    {"SEND", std::make_pair(0, 12)},
                    {"BACK", std::make_pair(0, 15)}
            };
    std::unordered_map<std::string, std::pair<int, int>> str_choose
            {
                    {"TYPE", std::make_pair(-20, -6)},
                    {"SIZE", std::make_pair(0, -6)},
                    {"NUMBER", std::make_pair(18, -6)}
            };
    std::vector<std::string> dhorizontal {"|", "|", "|", "|", "|", "|", "|"};

    choose = choose_pizza.find(grap.order_type);
    for (const auto &tmp : str_choose) {
        if (choose->second == tmp.first)
            grap.printBold(tmp.first, grap.cols / 2 + tmp.second.first, grap.lines / 2 + tmp.second.second);
        else
            grap.printDim(tmp.first, grap.cols / 2 + tmp.second.first, grap.lines / 2 + tmp.second.second);
    }
    for (const auto &tmp : str_order)
        grap.printString(tmp.first, grap.cols / 2 + tmp.second.first, grap.lines / 2 + tmp.second.second);

    grap.printString(dvertical, grap.cols / 2 - 30, grap.lines / 2 - 5);
    grap.print2D(dhorizontal, -30, -4, plazza::NORMAL);
    grap.print2D(dhorizontal, -7, -4, plazza::NORMAL);
    grap.print2D(dhorizontal, 9, -4, plazza::NORMAL);
    grap.print2D(dhorizontal, 31, -4, plazza::NORMAL);
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

void plazza::NPlazza::input_enter()
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
    } else if (opts_order == plazza::SEND)
        send = true;
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

void plazza::NPlazza::setInputOrder() {
    input = getInput();

    if (input == '\n')
        input_enter();
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

void plazza::NPlazza::printOrder()
{
    clearWindow();
    print2D(tOrder, 0, -17, NORMAL);
    displayOrder(*this);
    printCOrder(*this);
    refreshWindow();
    setInputOrder();
}


void plazza::NPlazza::setInputStatus()
{
    input = getInput();

    if (opts_status == MENU && input == '\n') {
        status.clear();
        nb_status = 0;
        opts_get = UNKNOWN;
    }
    if (!status.empty()) {
        if (opts_status == LEFT && input == '\n' && nb_status - 1 >= 0)
            nb_status--;
        if (opts_status == RIGHT && input == '\n' && nb_status + 1 < static_cast<int>(status.size()))
            nb_status++;
        if (input == KEY_DOWN)
            opts_status = MENU;
        if (input == KEY_LEFT && nb_status - 1 >= 0)
            opts_status = LEFT;
        if (input == KEY_RIGHT && nb_status + 1 < static_cast<int>(status.size()))
            opts_status = RIGHT;
    }
}

static void displayStatus(plazza::NPlazza grap)
{
    std::string back = "BACK";

    if (grap.nb_status - 1 >= 0)
        grap.print2D(plazza::tLrow, -80, -20, (grap.opts_status == plazza::LEFT) ? plazza::BOLD : plazza::DIM);
    if (grap.nb_status + 1 < static_cast<int>(grap.status.size()))
        grap.print2D(plazza::tRrow, 80, -20, (grap.opts_status == plazza::RIGHT) ? plazza::BOLD : plazza::DIM);
    if (grap.opts_status == plazza::MENU)
        grap.printBold(back, grap.cols / 2 - back.length() / 2, grap.lines / 2 + 15);
    else
        grap.printDim(back, grap.cols / 2 - back.length() / 2, grap.lines / 2 + 15);
}

static void printCStatus(plazza::NPlazza grap)
{
    size_t midx = grap.cols / 2;
    size_t midy = grap.lines / 2;
    std::unordered_map<pid_t, plazza::kitchen_status_t>::iterator it;

    if (grap.status.empty())
        grap.printString("All Kitchens are closed", midx - 11, midy);
    else {
        it = grap.status.begin();
        std::advance(it, grap.nb_status);
        std::string str = "Kitchen " + std::to_string(it->first);

        grap.printString(str, midx - 24, midy - 3);

        str = std::to_string(it->second.orders_waiting) + " orders waiting to be cooked";
        grap.printString(str, midx - 33, midy);

        str = std::to_string(it->second.orders_being_cooked) + " orders being cooked by";
        grap.printString(str, midx - 30, midy + 3);

        str = std::to_string(it->second.nb_cooks) + " cookers working";
        grap.printString(str, midx - 26, midy + 6);

        str = "Here is the left ingredients :";
        grap.printString(str, midx + 5, midy - 3);

        for (size_t i = 0; i < plazza::NbIngredients; i++) {
            str = "   - " + std::to_string(it->second.ingredients[i]) + ' ' +
                  plazza::ingredients_name.at(static_cast<plazza::PizzaIngredient>(i)) + " left";
            grap.printString(str, midx + 5, midy - 2 + i);
        }

    }
}

void plazza::NPlazza::printStatus(std::unordered_map<pid_t, kitchen_status_t> kitchens_stat)
{
    clearWindow();
    print2D(tStatus, 0, -20, NORMAL);
    if (status.empty()) {
        status = std::move(kitchens_stat);
        nb_status = 0;
    }
    displayStatus(*this);
    printCStatus(*this);
    refreshWindow();
    setInputStatus();
}
