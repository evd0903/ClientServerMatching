cmake_minimum_required(VERSION 3.21)
project(ClientServerEcn)

find_package(Boost 1.40 COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR src)

set(HEADER_DIR src)

set(SERVER_SOURCES
    ${SOURCE_DIR}/Server.cpp
    ${SOURCE_DIR}/Core.cpp
    ${SOURCE_DIR}/OrderBook.cpp
)

set(SERVER_HEADERS
    ${HEADER_DIR}/Core.h
    ${HEADER_DIR}/OrderBook.h
    ${HEADER_DIR}/Common.hpp
    ${HEADER_DIR}/json.hpp
)

add_executable(server ${SERVER_SOURCES} ${SERVER_HEADERS})
target_link_libraries(server PRIVATE Threads::Threads ${Boost_LIBRARIES})

set(CLIENT_SOURCES
    ${SOURCE_DIR}/Client.cpp
)

set(CLIENT_HEADERS
    ${HEADER_DIR}/Common.hpp
    ${HEADER_DIR}/json.hpp
)

add_executable(client ${CLIENT_SOURCES} ${CLIENT_HEADERS})
target_link_libraries(client PRIVATE Threads::Threads ${Boost_LIBRARIES})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(TEST_DIR tests)

set(TEST_SOURCES
    ${TEST_DIR}/TestCore.cpp
    ${SOURCE_DIR}/Core.cpp
    ${SOURCE_DIR}/OrderBook.cpp
)

add_executable(TestCore ${TEST_SOURCES})
target_link_libraries(TestCore PRIVATE ${GTEST_LIBRARIES} Threads::Threads ${Boost_LIBRARIES})

enable_testing()
add_test(NAME TestCore COMMAND TestCore)