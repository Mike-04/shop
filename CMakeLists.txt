cmake_minimum_required(VERSION 3.28)
project(shop)

set(CMAKE_CXX_STANDARD 14)
include_directories(.)

find_package(Qt5Widgets REQUIRED)

add_executable(shop
        domain.cpp
        domain.h
        tests.cpp
        tests.h
        tests.h
        main.cpp
        main.cpp
        repo.cpp
        repo.h
        repo.h
        service.cpp
        service.h
        service.h
        ui.cpp
        ui.h
        ui.h
        list.cpp
        list.h
        list.h
        list.h
        list.h
        utils.cpp
        utils.h
        undo.cpp
        undo.h
        gui.cpp
        gui.h
)

target_link_libraries(shop Qt5::Widgets)