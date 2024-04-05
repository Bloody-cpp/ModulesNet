cmake_minimum_required(VERSION 3.15)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

#Compiler sources
file(GLOB_RECURSE INC_FILES include/*.hpp ../lang/include/*.hpp)
file(GLOB_RECURSE SRC_FILES source/*.cpp ../lang/source/*.cpp)
add_executable(${PROJECT_NAME} ${INC_FILES} ${SRC_FILES})

include_directories(../lang/include)
include_directories(include)

find_package(Boost REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif ()

target_link_libraries(compiler PUBLIC ${Boost_LIBRARIES})
