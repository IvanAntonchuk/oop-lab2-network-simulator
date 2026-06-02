#ifndef OFFLINESTATE_H
#define OFFLINESTATE_H

#include "NodeState.h"

class OfflineState : public NodeState {
public:
    std::string handle(ServerNode* node) override;
};

#endif
