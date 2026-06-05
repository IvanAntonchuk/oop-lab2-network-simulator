cmake_minimum_required(VERSION 3.16)

project(NetworkSimulator VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    include
    include/core
    include/network
    include/patterns/creational
    include/patterns/structural
    include/patterns/behavioral
    include/visual
    gui
    src
)

file(GLOB_RECURSE SOURCES
    src/*.cpp
    gui/*.cpp
)
file(GLOB_RECURSE HEADERS
    include/*.h
    gui/*.h
)
file(GLOB_RECURSE FORMS
    gui/*.ui
)

add_executable(NetworkSimulator
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
)

target_link_libraries(NetworkSimulator PRIVATE Qt6::Widgets)
