#ifndef METRICSCOLLECTOR_H
#define METRICSCOLLECTOR_H

#include "SimulationObserver.h"

class MetricsCollector : public SimulationObserver {
public:
    std::string update(const std::string& event) override;
};

#endif
