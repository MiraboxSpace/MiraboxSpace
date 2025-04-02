//==============================================================================
/**
@file       main.cpp

@brief		Parse arguments and start the plugin
**/
//==============================================================================

#include "NlohmannJSONUtils.h"
#include "HSDConnectionManager.h"
#include "HSDLogger.h"

int esd_main(int argc, const char** argv, HSDBasePlugin* plugin) {
  if (argc != 9) {
      HSDLogger::LogMessage("Invalid number of parameters");
    return 1;
  }

  int port = 0;
  std::string pluginUUID;
  std::string registerEvent;
  std::string info;

  for (int argumentIndex = 0; argumentIndex < 4; argumentIndex++) {
    std::string parameter(argv[1 + 2 * argumentIndex]);
    std::string value(argv[1 + 2 * argumentIndex + 1]);

    if (parameter == kESDSDKPortParameter) {
      port = std::atoi(value.c_str());
    } else if (parameter == kESDSDKPluginUUIDParameter) {
      pluginUUID = value;
    } else if (parameter == kESDSDKRegisterEventParameter) {
      registerEvent = value;
    } else if (parameter == kESDSDKInfoParameter) {
      info = value;
    }
  }

  if (port == 0) {
      HSDLogger::LogMessage("Invalid port number");
    return 1;
  }

  if (pluginUUID.empty()) {
      HSDLogger::LogMessage("Invalid plugin UUID");
    return 1;
  }

  if (registerEvent.empty()) {
      HSDLogger::LogMessage("Invalid registerEvent");
    return 1;
  }

  if (info.empty()) {
      HSDLogger::LogMessage("Invalid info");
    return 1;
  }

  // Initialize localization helper
  std::string language = "en";
  try {
    json infoJson = json::parse(info);
    json applicationInfo;
    if (NlohmannJSONUtils::GetObjectByName(infoJson, kESDSDKApplicationInfo, applicationInfo)) {
      language = NlohmannJSONUtils::GetStringByName(applicationInfo, kESDSDKApplicationInfoLanguage, language);
    }
  } catch (...) {
  }

  // Create the connection manager
  HSDConnectionManager* connectionManager = new HSDConnectionManager(port, pluginUUID, registerEvent, info, plugin);
  HSDLogger::SetConnectionManager(connectionManager);

  // Connect and start the event loop
  connectionManager->Run();

  return 0;
}
