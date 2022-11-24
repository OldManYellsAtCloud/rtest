cmake_minimum_required(VERSION 3.0)

project(rumble LANGUAGES C)

add_executable(rumble main.c)

install(TARGETS rumble RUNTIME DESTINATION bin)

include_directories(SYSTEM)
