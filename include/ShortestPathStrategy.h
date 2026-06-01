#ifndef SHORTESTPATHSTRATEGY_H
#define SHORTESTPATHSTRATEGY_H

#include "RoutingStrategy.h"

class ShortestPathStrategy : public RoutingStrategy {
public:
    std::string route() override;
};

#endif
