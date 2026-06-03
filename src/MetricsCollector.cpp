#include "MetricsCollector.h"

std::string MetricsCollector::update(const std::string& event) {
    return "[MetricsCollector] Logged event: " + event + "\n";
}
