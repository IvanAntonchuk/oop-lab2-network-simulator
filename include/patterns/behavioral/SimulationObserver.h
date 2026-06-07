#ifndef SIMULATIONOBSERVER_H
#define SIMULATIONOBSERVER_H

#include <string>

/**
 * @brief Interface for objects that need to be notified of system changes (Observer pattern).
 * * Subscribers implement this interface to receive automatic updates.
 */
class SimulationObserver {
public:
    virtual ~SimulationObserver() = default;

    /** @brief Called by the publisher to notify the observer of a new event. */
    virtual std::string update(const std::string& event) = 0;
};

#endif
