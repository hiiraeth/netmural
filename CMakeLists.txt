cmake_minimum_required(VERSION 3.20)

project(netmural LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(NETCANVAS_WARNINGS_AS_ERRORS "Treat warnings as errors" OFF)

find_package(SFML CONFIG REQUIRED COMPONENTS Graphics Window System Network)

add_executable(netmural
    src/main.cpp
    # src/App.cpp
    # src/DataSource.cpp
    src/DataSource.cpp )

target_link_libraries(netmural
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Network
)

if (MSVC)
    target_compile_options(netmural PRIVATE /W4)
    if (NETCANVAS_WARNINGS_AS_ERRORS)
        target_compile_options(netmural PRIVATE /WX)
    endif()
else()
    target_compile_options(netmural PRIVATE -Wall -Wextra -Wpedantic)
    if (NETCANVAS_WARNINGS_AS_ERRORS)
        target_compile_options(netmural PRIVATE -Werror)
    endif()
endif()

if (APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
elseif(UNIX AND NOT APPLE)
    # e.g., vcpkg or system paths if you need them
    # include_directories(/usr/local/include)
    # link_directories(/usr/local/lib)
endif()

if (APPLE)
    set_target_properties(netmural PROPERTIES
        BUILD_WITH_INSTALL_RPATH ON
        INSTALL_RPATH "@executable_path/;@loader_path/"
    )
elseif(UNIX AND NOT APPLE)
    set_target_properties(netmural PROPERTIES
        BUILD_WITH_INSTALL_RPATH ON
        INSTALL_RPATH "\$ORIGIN"
    )
endif()