include(ExternalProject)

# Download url
# https://github.com/nlohmann/json/releases/download/v3.11.2/include.zip

ExternalProject_Add(
  json_source
  URL ${CMAKE_CURRENT_LIST_DIR}/include.zip
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(json_source SOURCE_DIR)
add_library(json INTERFACE)
add_dependencies(json json_source)
target_include_directories(
 json
  INTERFACE
  "${SOURCE_DIR}/single_include"
)

install(
  DIRECTORY
  "${SOURCE_DIR}/single_include/"
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
)
