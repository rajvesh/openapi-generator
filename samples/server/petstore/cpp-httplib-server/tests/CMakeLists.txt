cmake_minimum_required(VERSION 3.10)
project(PetstoreTests)

set(CMAKE_CXX_STANDARD 17)
include_directories(/usr/lib)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

find_package(nlohmann_json REQUIRED)

include_directories(
    ../
)

file(GLOB TEST_SOURCES *.cpp)
file(GLOB MODEL_SOURCES "../models/*.cpp")
file(GLOB API_SOURCES "../api/*.cpp")

add_library(models_objs OBJECT ${MODEL_SOURCES})
add_library(api_objs OBJECT ${API_SOURCES})

add_executable(runTests ${TEST_SOURCES} $<TARGET_OBJECTS:models_objs> $<TARGET_OBJECTS:api_objs>)

target_link_libraries(runTests
    GTest::GTest
    GTest::Main
    nlohmann_json::nlohmann_json
)

enable_testing()
add_test(NAME PetstoreTests COMMAND runTests)