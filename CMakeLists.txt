cmake_minimum_required(VERSION 3.16)

project(Practica3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Practica3 main.cpp
    structs.h structs.cpp
    LZ78.h LZ78.cpp
    README.md)

include(GNUInstallDirs)
install(TARGETS Practica3
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
