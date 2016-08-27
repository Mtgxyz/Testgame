cmake_minimum_required(VERSION 2.6)
project(testgame)

add_executable(testgame main.cpp)

install(TARGETS testgame RUNTIME DESTINATION bin)
