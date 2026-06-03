#ifndef NODEDECORATOR_H
#define NODEDECORATOR_H

#include "NetworkNode.h"
#include <memory>

class NodeDecorator : public NetworkNode {
protected:
    std::shared_ptr<NetworkNode> wrappee;

public:
    explicit NodeDecorator(std::shared_ptr<NetworkNode> node);

    std::string processTraffic() override;
    std::string getName() const override;
};

#endif
