cmake_minimum_required(VERSION 3.11)

project(
  game-server
  VERSION 1.0
  DESCRIPTION "game-server architecture"
  LANGUAGES CXX)

set (INCLUDE_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/include
)

set (SOURCE_FILES 
${CMAKE_CURRENT_SOURCE_DIR}/source/common/Thread.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkEngine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkEngineImpl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkEngineCore.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkSession.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkTcpSocket.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkUdpSocket.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/engine/NetworkServiceTcpBridge.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/UserClientTcpStub.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/network/UserClientTcpProxy.cpp
${CMAKE_CURRENT_SOURCE_DIR}/source/contents/UserClientHub.cpp
)

set(CMAKE_CXX_FLAGS -pthread)

add_executable (${CMAKE_PROJECT_NAME} main.cpp ${SOURCE_FILES})

find_package(PkgConfig)
pkg_check_modules(GLIBMM glibmm-2.4)

find_package(Boost REQUIRED)

include_directories(${INCLUDE_FILES} ${Boost_INCLUDE_DIRS} ${GLIBMM_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${Boost_LIBRARIES} ${GLIBMM_LIBRARIES})