#ifndef NODESTATE_H
#define NODESTATE_H

#include <string>

class ServerNode;

/**
 * @brief Interface defining the operational state of a server (State pattern).
 * * Extracts state-specific behavior into separate classes, allowing a server
 * to change its behavior dynamically.
 */
class NodeState {
public:
    virtual ~NodeState() = default;

    /** @brief Handles traffic based on the current state. */
    virtual std::string handle(ServerNode* node) = 0;

    /** @brief Determines if the server is active in this state. */
    virtual bool isOperational() const = 0;
};

#endif
