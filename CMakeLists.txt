cmake_minimum_required(VERSION 3.21)
project(ClientServerEcn)

find_package(Boost 1.40 COMPONENTS system REQUIRED)
find_package(Threads REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

# Директория для исходных файлов
set(SOURCE_DIR src)

# Директория для заголовочных файлов
set(HEADER_DIR src)

# Добавление исходных файлов для сервера
set(SERVER_SOURCES
    ${SOURCE_DIR}/Server.cpp
    ${SOURCE_DIR}/Core.cpp
    ${SOURCE_DIR}/OrderBook.cpp
)

# Добавление заголовочных файлов для сервера
set(SERVER_HEADERS
    ${HEADER_DIR}/Core.h
    ${HEADER_DIR}/OrderBook.h
    ${HEADER_DIR}/Common.hpp
    ${HEADER_DIR}/json.hpp
)

# Создание исполняемого файла для сервера
add_executable(Server ${SERVER_SOURCES} ${SERVER_HEADERS})
target_link_libraries(Server PRIVATE Threads::Threads ${Boost_LIBRARIES})

# Добавление исходных файлов для клиента
set(CLIENT_SOURCES
    ${SOURCE_DIR}/Client.cpp
)

# Добавление заголовочных файлов для клиента
set(CLIENT_HEADERS
    ${HEADER_DIR}/Common.hpp
    ${HEADER_DIR}/json.hpp
)

# Создание исполняемого файла для клиента
add_executable(Client ${CLIENT_SOURCES} ${CLIENT_HEADERS})
target_link_libraries(Client PRIVATE Threads::Threads ${Boost_LIBRARIES})
