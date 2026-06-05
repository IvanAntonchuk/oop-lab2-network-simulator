#include "OfflineState.h"
#include "ServerNode.h"

std::string OfflineState::handle(ServerNode* node) {
    return "[OFFLINE] Сервер вимкнено. Пакети відхиляються";
}
