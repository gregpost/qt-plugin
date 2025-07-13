cmake_minimum_required(VERSION 3.16)
project(MyPlugin)

find_package(Qt6 COMPONENTS Core REQUIRED)
set(CMAKE_AUTOMOC ON)

add_library(myplugin SHARED
    MyPlugin.cpp
    ${CMAKE_SOURCE_DIR}/PluginInterface.h    # ← ссылка на корневой файл
)

# Чтобы #include "PluginInterface.h" работал
target_include_directories(myplugin
    PRIVATE
        ${CMAKE_SOURCE_DIR}
)

target_link_libraries(myplugin PRIVATE Qt6::Core)
