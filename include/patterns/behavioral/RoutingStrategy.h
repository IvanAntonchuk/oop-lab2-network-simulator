#ifndef ROUTINGSTRATEGY_H
#define ROUTINGSTRATEGY_H

#include <string>

class RoutingStrategy {
public:
    virtual ~RoutingStrategy() = default;
    virtual std::string route() = 0;
};

#endif
