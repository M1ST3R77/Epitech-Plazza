/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPC.hpp
*/

#pragma once

#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <random>
#include <sys/select.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <functional>

#include "../Exceptions/Exceptions.hpp"

class IPC {
public:
    IPC();
    ~IPC();

    IPC &operator<<(const std::string &message);
    IPC &operator>>(std::string &message);

    template <typename T>
    IPC &operator<<(const T &message) {
        msgbuf_t msg = {1, {}};
        std::memcpy(msg.mtext, &message, sizeof(T));
        if (msgsnd(queue_id, &msg, sizeof(T), IPC_NOWAIT) == -1)
            throw exceptions::ProcessError("Can't write on queue " + std::to_string(queue_id) + ": " + std::strerror(errno));
        return *this;
    }

    template <typename T>
    IPC &operator>>(T &message) {
        msgbuf_t msg;
        if (msgrcv(queue_id, &msg, sizeof(T), 1, 0) == -1)
            throw exceptions::ProcessError("Can't receive on queue " + std::to_string(queue_id) + ": " + std::strerror(errno));
        std::memcpy(&message, msg.mtext, sizeof(T));
        return *this;
    }

    void destruct() const;
    [[nodiscard]] bool contentWaiting() const;

private:
    typedef struct msgbuf_s {
        long mtype;
        char mtext[1024];
    } msgbuf_t;

    int queue_id;
};
