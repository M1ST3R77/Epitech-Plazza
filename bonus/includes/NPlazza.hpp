/*
** EPITECH PROJECT, 2024
** B-CCP-400_bonus_theplazza
** File description:
** NPlazza.hpp
*/

#pragma once

#include "NCurses.hpp"
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

    class NPlazza : public NCurses {
    public:
        NPlazza();
        ~NPlazza() = default;

        void printTitle(opts_enum opt);
        void printOpts();
        void displayHelp();
        void displayOrder();

        void printStart();
        void printOrder();
        void printHelp();

        int input = 0;
        int lines = 0;
        int cols = 0;
        opts_enum opts_choose = ORDER;
        opts_enum opts_get = UNKNOWN;
        cOrder_enum opts_order = ORD;
    };

}
