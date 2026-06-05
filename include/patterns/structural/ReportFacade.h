#ifndef REPORTFACADE_H
#define REPORTFACADE_H

#include "NetworkNode.h"
#include "SimulationManager.h"
#include <string>
#include <memory>

class ReportFacade {
private:
    std::shared_ptr<NetworkNode> network;

public:
    explicit ReportFacade(std::shared_ptr<NetworkNode> net);
    std::string generateNetworkReport();
};

#endif
