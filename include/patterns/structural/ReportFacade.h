#ifndef REPORTFACADE_H
#define REPORTFACADE_H

#include "NetworkNode.h"
#include <string>
#include <memory>
#include <vector>

/**
 * @brief Provides a simplified interface for generating network diagnostics (Facade pattern).
 * * Hides the complexity of traversing the network, analyzing nodes,
 * and collecting statistics behind a single easy-to-use class.
 */
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
