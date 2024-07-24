set(
  SOURCES
  HSDAction.cpp
  HSDConnectionManager.cpp
  HSDLogger.cpp
  HSDMain.cpp
  HSDPlugin.cpp
)

add_library(
  StreamDockSDK
  STATIC
  ${SOURCES}
)
target_compile_definitions(StreamDockSDK PRIVATE JSON_USE_IMPLICIT_CONVERSIONS=0)
target_link_libraries(
  StreamDockSDK
  PUBLIC
  asio
  json
  websocketpp
)

file(GLOB HEADERS *.h)
set_target_properties(
  StreamDockSDK
  PROPERTIES
  PUBLIC_HEADER "${HEADERS}"
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
target_include_directories(StreamDockSDK PUBLIC "${CMAKE_CURRENT_LIST_DIR}/..")

install(
  TARGETS
  StreamDockSDK
  PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/StreamDockSDK"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)
