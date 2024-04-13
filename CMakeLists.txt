cmake_minimum_required(VERSION 3.8.0)
project(converter VERSION 0.1.0 LANGUAGES C CXX)

# add_library(converter converter.cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS ON)

include_directories(include)

include(CTest)
enable_testing()
include(test/test.cmake)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
