#ifndef RANDOMPATHSTRATEGY_H
#define RANDOMPATHSTRATEGY_H

#include "RoutingStrategy.h"

class RandomPathStrategy : public RoutingStrategy {
public:
    std::string route() override;
};

#endif
