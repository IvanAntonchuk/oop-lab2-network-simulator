#ifndef ONLINESTATE_H
#define ONLINESTATE_H

#include "NodeState.h"

/**
 * @brief Represents the normal, operational state of a server.
 * * In this state, the server actively processes and routes traffic.
 */
class OnlineState : public NodeState {
public:
    std::string handle(ServerNode* node) override;
    bool isOperational() const override;
};

#endif
