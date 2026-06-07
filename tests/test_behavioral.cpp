#include <gtest/gtest.h>
#include "HistoryManager.h"
#include "SimulationCommand.h"
#include "SimulationManager.h"
#include "ServerNode.h"
#include "OfflineState.h"
#include "OnlineState.h"
#include "ShortestPathStrategy.h"
#include <memory>

class DummyCommand : public ICommand {
private:
    int& testValue;
public:
    DummyCommand(int& val) : testValue(val) {}
    void execute() override { testValue += 10; }
    void undo() override { testValue -= 10; }
};

TEST(BehavioralPatternsTest, HistoryManagerUndoRedoWorks) {
    HistoryManager history(&SimulationManager::getInstance());
    int stateValue = 0;

    auto cmd = std::make_unique<DummyCommand>(stateValue);
    history.executeCommand(std::move(cmd));

    EXPECT_EQ(stateValue, 10) << "Command failed: execute() was not called.";

    history.undo();
    EXPECT_EQ(stateValue, 0) << "Command failed: undo() did not revert the state.";

    history.redo();
    EXPECT_EQ(stateValue, 10) << "Command failed: redo() did not re-apply the state.";
}

TEST(BehavioralPatternsTest, StateChangesNodeBehavior) {
    auto server = std::make_shared<ServerNode>("State-Server");

    EXPECT_NO_THROW(server->changeState(std::make_shared<OfflineState>()))
        << "State failed: changeState threw an exception.";

    EXPECT_NO_THROW(server->processTraffic())
        << "State failed: processTraffic crashed while in OfflineState.";
}

TEST(BehavioralPatternsTest, StrategyCalculatesPathCorrectly) {
    auto nodeA = std::make_shared<ServerNode>("NodeA");
    auto nodeB = std::make_shared<ServerNode>("NodeB");

    nodeA->connectTo(nodeB);
    nodeB->connectTo(nodeA);

    ShortestPathStrategy strategy;
    auto path = strategy.calculatePath(nodeA, nodeB);

    EXPECT_FALSE(path.empty()) << "Strategy failed: Path calculation returned empty path for connected nodes.";

    EXPECT_EQ(path.back()->getName(), "NodeB") << "Strategy failed: The final node in the path is incorrect.";
}
