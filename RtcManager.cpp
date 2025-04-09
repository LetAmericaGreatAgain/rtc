//
// Created by universe on 2025/3/25.
//

#include "RtcManager.h"


RtcManager::RtcManager(std::string& localId) : localId(localId) {
    std::cout << localId << " --- " << std::endl;
}

void RtcManager::setLocalId(std::string &localId) {
    this->localId = localId;
}



