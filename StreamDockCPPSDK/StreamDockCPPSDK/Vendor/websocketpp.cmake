include(ExternalProject)

# Download url
# https://github.com/zaphoyd/websocketpp/archive/refs/tags/0.8.2.zip
# https://github.com/zaphoyd/websocketpp/archive/refs/tags/0.8.2.tar.gz

ExternalProject_Add(
  websocketpp_source
  URL ${CMAKE_CURRENT_LIST_DIR}/websocketpp-0.8.2.zip
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(websocketpp_source SOURCE_DIR)
add_library(websocketpp INTERFACE)
add_dependencies(websocketpp websocketpp_source)
set_target_properties(
  websocketpp
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED ON
  CXX_EXTENSIONS OFF
)
target_include_directories(
  websocketpp
  INTERFACE
  "${SOURCE_DIR}"
)
target_link_libraries(
  websocketpp
  INTERFACE
  asio
)
target_compile_definitions(
  websocketpp
  INTERFACE
  ASIO_STANDALONE=1
)
if(MSVC)
  target_compile_options(
    websocketpp
    INTERFACE
    "/Zc:__cplusplus"
  )
endif()

install(
	DIRECTORY
	"${SOURCE_DIR}/websocketpp"
	DESTINATION
	"${CMAKE_INSTALL_INCLUDEDIR}"
)
