cmake_minimum_required(VERSION 3.30)
project(Vehicle_System)

set(CMAKE_CXX_STANDARD 20)

add_executable(Vehicle_System main.cpp
        src/customer_system.cpp
        src/vehicle_system.cpp
        src/globals.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/release-1.12.1.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(system_test test/system_test.cpp
        src/customer_system.cpp
        src/globals.cpp
        src/vehicle_system.cpp)

target_include_directories(system_test PRIVATE include)
target_link_libraries(system_test gtest_main)

include(GoogleTest)
gtest_discover_tests(system_test)