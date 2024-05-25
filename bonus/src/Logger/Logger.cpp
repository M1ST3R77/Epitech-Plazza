/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Logger.cpp
*/

#include "Logger.hpp"

#include <ctime>
#include <fstream>

void Logger::log(const std::string &msg, const LogLevel log_level) {
    std::ofstream log_file("log.txt", std::ofstream::app);
    const std::time_t now = std::time(nullptr);
    std::string asctime = std::asctime(std::localtime(&now));
    asctime.pop_back();
    log_file << '[' + asctime.substr() + "] " + log_levels[log_level] + " : " + msg + '\n';
    log_file.close();
}
