#include "HSDExampleAction.h"

#include "StreamDockCPPSDK/StreamDockSDK/NlohmannJSONUtils.h"
#include "StreamDockCPPSDK/StreamDockSDK/HSDLogger.h"

void HSDExampleAction::DidReceiveSettings(const nlohmann::json& payload) {
    HSDLogger::LogMessage("DidReceiveSettings");
}

void HSDExampleAction::KeyDown(const nlohmann::json& payload) {
    HSDLogger::LogMessage("KeyDown");
    if (NlohmannJSONUtils::GetIntByName(payload, "state") == 0) {
        SetState(1);
    }
    else {
        SetState(0);
    }
}

void HSDExampleAction::KeyUp(const nlohmann::json& payload) {
    // Log in release and debug builds
    HSDLogger::LogMessage("KeyUp");
    ShowOK();
    // Only log in debug builds (C++20-style format strings):
    nlohmann::json settings = payload["settings"];
    HSDLogger::LogMessage("Settings: " + settings.dump());
}

void HSDExampleAction::WillAppear(const nlohmann::json& payload) {
    HSDLogger::LogMessage("WillAppear");
}

void HSDExampleAction::SendToPlugin(const nlohmann::json& payload) {
    HSDLogger::LogMessage("Received message from property inspector: " + payload.dump());
}