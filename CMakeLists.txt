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

# КОНФІГУРАЦІЯ ДЛЯ GOOGLETEST

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/gui/*.cpp"
)

list(FILTER TEST_CORE_SOURCES EXCLUDE REGEX "main\\.cpp$")

file(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

add_executable(NetworkSimulator_Tests
    ${TEST_CORE_SOURCES}
    ${HEADERS}
    ${FORMS}
    ${TEST_FILES}
)

target_link_libraries(NetworkSimulator_Tests PRIVATE
    gtest
    gtest_main
    Qt6::Widgets
)

enable_testing()
add_test(NAME NetworkTests COMMAND NetworkSimulator_Tests)
