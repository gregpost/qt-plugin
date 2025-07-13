# Убедитесь, что Qt6::Network добавлен
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)

add_executable(MainApp
    MainWindow.h
    main.cpp
)

target_include_directories(MainApp
    PRIVATE ${CMAKE_SOURCE_DIR}
)

target_link_libraries(MainApp
    PRIVATE Qt6::Core Qt6::Widgets Qt6::Network
)
