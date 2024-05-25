/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** Logger.hpp
*/

#pragma once

#include <string>
#include <unordered_map>

class Logger {
public:
    enum LogLevel {
        Debug,
        Info,
        Warning,
        Error,
        Critical
    };

    static void log(const std::string &msg, LogLevel log_level);

    static inline std::unordered_map<LogLevel, std::string> log_levels = {
        {Debug, "DEBUG"},
        {Info, "INFO"},
        {Warning, "WARNING"},
        {Error, "ERROR"},
        {Critical, "CRITICAL"}
    };
};
