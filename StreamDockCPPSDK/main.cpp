#include "HSDExamplePlugin.h"

#include "StreamDockCPPSDK/StreamDockSDK/HSDMain.h"

int main(int argc, const char** argv) {
  auto plugin = std::make_unique<HSDExamplePlugin>();
  return esd_main(argc, argv, plugin.get());
}
