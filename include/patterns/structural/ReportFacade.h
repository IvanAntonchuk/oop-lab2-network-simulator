#ifndef REPORTFACADE_H
#define REPORTFACADE_H

#include "NetworkNode.h"
#include <string>
#include <memory>
#include <vector>

class ReportFacade {
private:
    std::shared_ptr<NetworkNode> network;
    std::vector<std::vector<std::shared_ptr<NetworkNode>>> calculatedPaths;

public:
    explicit ReportFacade(std::shared_ptr<NetworkNode> net);

    std::string generateNetworkReport();
    std::vector<std::vector<std::shared_ptr<NetworkNode>>> getCalculatedPaths() const;
};

#endif
