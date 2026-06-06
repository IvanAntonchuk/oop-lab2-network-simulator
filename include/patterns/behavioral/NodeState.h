#ifndef NODESTATE_H
#define NODESTATE_H

#include <string>

class ServerNode;

class NodeState {
public:
    virtual ~NodeState() = default;
    virtual std::string handle(ServerNode* node) = 0;
    virtual bool isOperational() const = 0;
};

#endif
