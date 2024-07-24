/* Copyright (c) 2020-present, Fred Emmott
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file.
 */

#pragma once

#include "HSDAction.h"

/** An `HSDAction` where state can be changed by something other than the
 * StreamDock software.
 *
 * For example:
 * - hardware events
 * - time
 * - changes in other applications that the plugin interacts with (e.g. OBS)
 *
 * In these cases, you likely want to consider settings to be persistent, and
 * 'settings changed' to be an event in itself. This class removes the settings
 * parameter (which may be changed or unchanged) from most events, and adds a
 * new event for when they've changed.
 */
template <class TSettings>
class HSDActionWithExternalState : public HSDAction {
 protected:
  virtual void SettingsDidChange(
    const TSettings& old_settings, 
    const TSettings& new_settings) = 0;

  virtual void WillAppear() {
  }

  virtual void KeyDown() {
  }

  virtual void KeyUp() {
  }

  const TSettings& GetSettings() const {
    return mSettings;
  }

 public:
  HSDActionWithExternalState(
    HSDConnectionManager* hsd_connection, 
    const std::string& action, 
    const std::string& context)
    : HSDAction(hsd_connection, action, context) {
  }

  virtual ~HSDActionWithExternalState() {
  }

  virtual void DidReceiveSettings(const nlohmann::json& json_settings) final {
    TSettings new_settings(json_settings);
    if (new_settings == mSettings) {
      return;
    }
    const auto old_settings = std::move(mSettings);
    mSettings = std::move(new_settings);
    SettingsDidChange(old_settings, mSettings);
  }

  virtual void WillAppear(const nlohmann::json& settings) final {
    DidReceiveSettings(settings);
    WillAppear();
  }

  virtual void KeyUp(const nlohmann::json& settings) final {
    DidReceiveSettings(settings);
    KeyUp();
  }

  virtual void KeyDown(const nlohmann::json& settings) final {
    DidReceiveSettings(settings);
    KeyDown();
  }

 private:
  TSettings mSettings;
};
