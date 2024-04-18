cmake_minimum_required(VERSION 3.15)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

include_directories(compiler "lang/include")
include_directories(compiler include)

file(GLOB_RECURSE INC_FILES include/*.hpp lang/include/*.hpp)
file(GLOB_RECURSE SRC_FILES source/*.cpp lang/source/*.cpp)
add_executable(${PROJECT_NAME} ${INC_FILES} ${SRC_FILES})

find_package(Boost REQUIRED COMPONENTS program_options)
target_link_libraries(compiler PRIVATE Boost::boost Boost::program_options)