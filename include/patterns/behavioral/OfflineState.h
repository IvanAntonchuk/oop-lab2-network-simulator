#ifndef OFFLINESTATE_H
#define OFFLINESTATE_H

#include "NodeState.h"

/**
 * @brief Represents a failed or disabled state of a server.
 * * In this state, the server drops packets and is ignored by routing algorithms.
 */
class OfflineState : public NodeState {
public:
    std::string handle(ServerNode* node) override;
    bool isOperational() const override;
};

#endif
