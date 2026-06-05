#include "NodeDecorator.h"

NodeDecorator::NodeDecorator(std::shared_ptr<NetworkNode> node)
    : NetworkNode(node ? node->getName() + "_decorated" : "unknown"), wrappee(node) {}

std::string NodeDecorator::processTraffic() {
    if (wrappee) {
        return wrappee->processTraffic();
    }
    return "";
}

std::string NodeDecorator::getName() const {
    if (wrappee) {
        return wrappee->getName();
    }
    return name;
}
