#ifndef ONLINESTATE_H
#define ONLINESTATE_H

#include "NodeState.h"

class OnlineState : public NodeState {
public:
    std::string handle(ServerNode* node) override;
    bool isOperational() const override;
};

#endif
