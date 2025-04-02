// @copyright  (c) 2022, ljj
// This source code is licensed under the MIT-style license found in the LICENSE file.

#include "HSDLogger.h"

#include "HSDConnectionManager.h"

namespace {
HSDConnectionManager* sConnectionManager = nullptr;
}// namespace

void HSDLogger::SetConnectionManager(HSDConnectionManager* hsd_connection) {
  sConnectionManager = hsd_connection;
}

void HSDLogger::LogMessage(const std::string& message) {
  if (sConnectionManager) {
      sConnectionManager->LogMessage(message);
  }
}
