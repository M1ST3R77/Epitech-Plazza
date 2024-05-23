/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NCurses.cpp
*/

#include "NCurses.hpp"

plazza::NCurses::NCurses()
{
    initscr();
    keypad(stdscr, TRUE);
    noecho();
    set_escdelay(0);
    curs_set(0);
}

plazza::NCurses::~NCurses()
{
    endwin();
}

void plazza::NCurses::printString(const std::string& str, int x, int y)
{
    mvprintw(y, x, "%s", str.c_str());
}

void plazza::NCurses::printDim(const std::string &str, int x, int y)
{
    attron(A_DIM);
    mvprintw(y, x, "%s", str.c_str());
    attroff(A_DIM);
}

void plazza::NCurses::printBold(const std::string &str, int x, int y)
{
    attron(A_BOLD);
    mvprintw(y, x, "%s", str.c_str());
    attroff(A_BOLD);
}

void plazza::NCurses::printEmpty(int x, int y, int len)
{
    mvprintw(y, x, "%*s", len, "");
}

void plazza::NCurses::refreshWindow()
{
    refresh();
}

int plazza::NCurses::getInput()
{
    return getch();
}

void plazza::NCurses::clearWindow()
{
    clear();
}
