cmake_minimum_required(VERSION 3.16)
project(PluginRunner)

find_package(Qt6 COMPONENTS Core Network REQUIRED)  # добавлен Network
set(CMAKE_AUTOMOC ON)

add_executable(PluginRunner
    main.cpp
    PluginDaemon.h
)

target_include_directories(PluginRunner
    PRIVATE
        ${CMAKE_SOURCE_DIR}  # корень проекта, где лежит PluginInterface.h
)

target_link_libraries(PluginRunner
    PRIVATE Qt6::Core Qt6::Network  # добавлена Qt6::Network
)
