cmake_minimum_required(VERSION 3.16)
project(QtPluginReloadDemo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

# ──────────────────────────────────────────────────────────────────────────────
# Единая папка для всех .exe и .dll (runtime + library).
# Для много-конфигурных генераторов (Visual Studio) прописываем все конфигурации.
# ──────────────────────────────────────────────────────────────────────────────
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY         ${OUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY         ${OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY         ${CMAKE_BINARY_DIR}/lib)

if(CMAKE_CONFIGURATION_TYPES)  # Visual Studio, Xcode и др.
  foreach(_CONFIG IN LISTS CMAKE_CONFIGURATION_TYPES)
    string(TOUPPER "${_CONFIG}" _CFG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_CFG} ${OUTPUT_DIR})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_CFG} ${OUTPUT_DIR})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_CFG} ${CMAKE_BINARY_DIR}/lib)
  endforeach()
endif()
# ──────────────────────────────────────────────────────────────────────────────

add_subdirectory(plugin)
add_subdirectory(pluginrunner)
add_subdirectory(mainapp)
