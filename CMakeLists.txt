cmake_minimum_required(VERSION 3.14)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()


add_library(${PROJECT_NAME}_lib
    src/array.cpp
    src/figure.cpp
    src/point.cpp
)

target_include_directories(${PROJECT_NAME}_lib PUBLIC includes)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_tests tests/tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME}_lib gtest_main)

if(UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
    target_link_libraries(${PROJECT_NAME}_tests PRIVATE m)
    target_link_libraries(${PROJECT_NAME}_lib PUBLIC m)
endif()

enable_testing()

add_test(NAME ${PROJECT_NAME}_tests COMMAND ${PROJECT_NAME}_tests)
