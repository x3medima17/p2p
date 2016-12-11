cmake_minimum_required(VERSION 3.6)
project(KaZaA)

SET(CMAKE_CXX_COMPILER g++-6)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic -Wextra -Wshadow")

#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lstdc++fs")

include_directories (./include)

file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
set(SOURCE_FILES ${SOURCES})

add_executable(super ${SOURCE_FILES} super.cpp)
add_executable(child ${SOURCE_FILES} child.cpp)

target_link_libraries(child stdc++fs)

add_custom_command(TARGET super
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:super> ${PROJECT_SOURCE_DIR}/env/super/)



add_custom_command(TARGET child
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:child> ${PROJECT_SOURCE_DIR}/env/child/child1)

add_custom_command(TARGET child
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:child> ${PROJECT_SOURCE_DIR}/env/child/child2)

add_custom_command(TARGET child
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:child> ${PROJECT_SOURCE_DIR}/env/child/child2)
