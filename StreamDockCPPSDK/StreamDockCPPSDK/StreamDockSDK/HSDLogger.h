// @copyright  (c) 2020, Frederick Emmott
// This source code is licensed under the MIT-style license found in the LICENSE file.
#pragma once

#include <string>

class HSDConnectionManager;

class HSDLogger final {
 public:
  HSDLogger() = delete;
  static void SetConnectionManager(HSDConnectionManager* hsd_connection);

  static void LogMessage(const std::string& message);
};