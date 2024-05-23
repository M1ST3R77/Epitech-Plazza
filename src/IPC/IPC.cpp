/*
** EPITECH PROJECT, 2024
** B-OOP-300_plazza
** File description:
** IPC.cpp
*/

#include "IPC.hpp"

IPC::IPC() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution distribution(0, INT32_MAX);

    auto generate_key = std::bind(distribution, generator);

    queue_id = msgget(generate_key(), IPC_CREAT | IPC_EXCL | 0666);
    while (queue_id == -1) {
        if (errno != EEXIST) {
            throw exceptions::ProcessError("Can't create IPC message queue: " + std::string(std::strerror(errno)));
        }
        queue_id = msgget(generate_key(), IPC_CREAT | IPC_EXCL | 0666);
    }
}

IPC::~IPC() {
    destruct();
}

IPC &IPC::operator<<(const std::string &message) {
    msgbuf_t msg = {1, {}};
    if (message.size() >= sizeof(msg.mtext))
        throw exceptions::ProcessError("Message too long for queue");
    std::strncpy(msg.mtext, message.c_str(), sizeof(msg.mtext));
    msg.mtext[sizeof(msg.mtext) - 1] = '\0';

    if (msgsnd(queue_id, &msg, std::strlen(msg.mtext) + 1, IPC_NOWAIT) == -1)
        throw exceptions::ProcessError("Can't write on queue " + std::to_string(queue_id) + ": " + std::strerror(errno));
    return *this;
}

IPC &IPC::operator>>(std::string &message) {
    msgbuf_t msg;
    if (msgrcv(queue_id, &msg, sizeof(msg.mtext), 1, 0) == -1)
        throw exceptions::ProcessError("Can't receive on queue " + std::to_string(queue_id) + ": " + std::strerror(errno));
    message = msg.mtext;
    return *this;
}

void IPC::destruct() const {
    msgctl(queue_id, IPC_RMID, nullptr);
}

bool IPC::contentWaiting() const {
    struct msqid_ds buf{};
    if (msgctl(queue_id, IPC_STAT, &buf) == -1)
        return false;
    return buf.msg_qnum > 0;
}
