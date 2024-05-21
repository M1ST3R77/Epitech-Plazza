/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.hpp
*/

#pragma once

#include "NCurses.hpp"
#include "Command.hpp"
#include "../src/Shell/Shell.hpp"
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
                    "   #########  #########  ##         ##       ",
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
                    "  ##      ##  ## ##       ##      ##  ##########  ## ##     ",
                    "  ##      ##  ##   ##     ##      ##  ##          ##   ##   ",
                    "  ##      ##  ##    ##    ##      ##  ##          ##    ##  ",
                    "  ##########  ##      ##  #########   ##########  ##      ##"
            };

    enum opts_enum {
        ORDER,
        DETAILS,
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

        void printTitle(opts_enum opt);
        void setInputOrder(Shell shell);

        void printStart();
        void printOrder(Shell shell);
        void printHelp();

        int input = 0;
        int lines = 0;
        int cols = 0;


        Ccommand_t choose_cmd = {Margarita, M, 4, 2};
        std::vector<command_t> commands;
        OType_enum order_type = TYPE;

        opts_enum opts_choose = ORDER;
        opts_enum opts_get = UNKNOWN;
        cOrder_enum opts_order = ORD;
    };

}
