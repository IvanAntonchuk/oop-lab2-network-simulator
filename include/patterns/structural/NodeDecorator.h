#ifndef NODEDECORATOR_H
#define NODEDECORATOR_H

#include "NetworkNode.h"
#include <memory>

/**
 * @brief Base decorator class for dynamically adding behavior to nodes (Decorator pattern).
 * * Wraps a NetworkNode and delegates traffic processing to it, allowing
 * subclasses to add pre- or post-processing logic.
 */
class NodeDecorator : public NetworkNode {
protected:
    std::shared_ptr<NetworkNode> wrappee;

public:
    explicit NodeDecorator(std::shared_ptr<NetworkNode> node);

    std::string processTraffic() override;
    std::string getName() const override;
    bool isOperational() const override;
};

#endif
