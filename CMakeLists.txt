cmake_minimum_required(VERSION 3.16)
project(SysCore LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(SysCore
    SysCore.cpp
    lexer.cpp
    lexer.hpp
)

if(WIN32 AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/SysCore.rc")
    target_sources(SysCore PRIVATE SysCore.rc)
endif()