/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.hpp
*/

#pragma once

#include "NCurses.hpp"
#include "Command.hpp"
#include "../Kitchen/Kitchen.hpp"
#include <unordered_map>
#include <vector>

namespace plazza {

    inline std::vector<std::string> tPlazza =
            {
                    "#######  #             #       ###########  ###########       #",
                    "#     #  #            # #              ##           ##       # #",
                    "#######  #           #   #          ##           ##         #   #",
                    "#        #          #######       ##           ##          #######",
                    "#        #         #       #    ##           ##           #       #",
                    "#        #######  #         #  ###########  ###########  #         #"
            };

    inline std::vector<std::string> tHelp =
            {
                    "   ##     ##  #########  ##         #########",
                    "   ##     ##  ##         ##         ##     ##",
                    "   ##     ##  ##         ##         ##     ##",
                    "   #########  #########  ##         #########",
                    "   ##     ##  ##         ##         ##       ",
                    "   ##     ##  ##         ##         ##       ",
                    "   ##     ##  ##         ##         ##       ",
                    "   ##     ##  #########  #########  ##       "
            };

    inline std::vector<std::string> tOrder =
            {
                    "  ##########  ##########  #########   ##########  ##########",
                    "  ##      ##  ##      ##  ##      ##  ##          ##      ##",
                    "  ##      ##  ##      ##  ##      ##  ##          ##      ##",
                    "  ##      ##  ##########  ##      ##  ##########  ##########",
                    "  ##      ##  ## ##       ##      ##  ##          ## ##     ",
                    "  ##      ##  ##   ##     ##      ##  ##          ##   ##   ",
                    "  ##      ##  ##    ##    ##      ##  ##          ##    ##  ",
                    "  ##########  ##      ##  #########   ##########  ##      ##"
            };

    inline std::vector<std::string> tStatus =
            {
                    "##########  ##########         #         ##########  ##      ##  ##########",
                    "##              ##            # #            ##      ##      ##  ##        ",
                    "##              ##           #   #           ##      ##      ##  ##        ",
                    "##########      ##          #     #          ##      ##      ##  ##########",
                    "        ##      ##         #########         ##      ##      ##          ##",
                    "        ##      ##        #         #        ##      ##      ##          ##",
                    "        ##      ##       #           #       ##      ##      ##          ##",
                    "##########      ##      #             #      ##      ##########  ##########"
            };

    inline std::vector<std::string> tRrow =
            {
                    "         ##   ",
                    "          ##  ",
                    "##############",
                    "##############",
                    "          ##  ",
                    "         ##   "
            };

    inline std::vector<std::string> tLrow =
            {
                    "   ##         ",
                    "  ##          ",
                    "##############",
                    "##############",
                    "  ##          ",
                    "   ##         "
            };

    enum config_enum {
        NORMAL,
        BOLD,
        DIM
    };

    enum opts_enum {
        ORDER,
        STATUS,
        HELP,
        EXIT,
        UNKNOWN
    };

    enum cOrder_enum {
        ORD,
        ADD,
        SEND,
        BACK
    };

    enum OType_enum {
        TYPE,
        SIZE,
        D1,
        D2,
    };

    enum status_enum {
        LEFT,
        RIGHT,
        MENU
    };

    typedef struct Ccommand_s {
        PizzaType pizza;
        PizzaSize size;
        int d1;
        int d2;
    } Ccommand_t;

    class NPlazza : public NCurses {
    public:
        NPlazza();
        ~NPlazza() = default;

        void print2D(const std::vector<std::string>& elem, int xpos, int ypos, config_enum conf);
        void setInputOrder();
        void setInputStatus();
        void input_enter();
        void choose_order(float mult, int numb);

        void printStart();
        void printOrder();
        void printStatus(std::unordered_map<pid_t, kitchen_status_t> kitchens_stat);
        void printHelp();

        int input = 0;
        int lines = 0;
        int cols = 0;
        bool send = false;

        opts_enum opts_choose = ORDER;
        opts_enum opts_get = UNKNOWN;

        Ccommand_t choose_cmd = {Margarita, M, 4, 2};
        std::vector<command_t> commands;
        OType_enum order_type = TYPE;
        cOrder_enum opts_order = ORD;

        int nb_status = 0;
        std::unordered_map<pid_t, kitchen_status_t> status;
        status_enum opts_status = MENU;
    };

}
