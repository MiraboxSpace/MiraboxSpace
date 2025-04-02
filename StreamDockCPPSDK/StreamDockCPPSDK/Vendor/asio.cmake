include(ExternalProject)

# Download url
# https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-27-0.zip
# https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-27-0.tar.gz

ExternalProject_Add(
  asio_source
  URL ${CMAKE_CURRENT_LIST_DIR}/asio-asio-1-27-0.zip
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(asio_source SOURCE_DIR)
add_library(asio INTERFACE)
add_dependencies(asio asio_source)
set_target_properties(
  asio
  PROPERTIES
  CXX_STANDARD 20
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIOSN OFF
)
target_compile_definitions(
  asio
  INTERFACE
  ASIO_STANDALONE=1
)
target_include_directories(
  asio
  INTERFACE
  ${SOURCE_DIR}/asio/include
)

install(
  DIRECTORY
  ${SOURCE_DIR}/asio/include/
  DESTINATION
  "${CMAKE_INSTALL_INCLUDEDIR}"
  FILES_MATCHING
  PATTERN "*.hpp"
  PATTERN "*.ipp"
)

# Work around https://github.com/chriskohlhoff/asio/issues/1090
if(APPLE AND "${CMAKE_OSX_DEPLOYMENT_TARGET}" VERSION_LESS "10.15")
  target_compile_definitions(
    asio
    INTERFACE
    "ASIO_DISABLE_STD_ALIGNED_ALLOC=1"
  )
endif()
