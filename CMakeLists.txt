cmake_minimum_required(VERSION 3.13) 
project(chess)

set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5 COMPONENTS graphics window REQUIRED)

add_executable(chess src/main.cpp)

target_link_libraries(chess sfml-graphics sfml-audio)