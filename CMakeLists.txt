cmake_minimum_required(VERSION 3.27)
project(plazza)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        plazza
)

set(SRC src/Main.cpp
        src/Shell.hpp
        src/Shell.cpp
        src/Exceptions.hpp
        src/Exceptions.cpp
)

include_directories(includes)

add_executable(plazza ${SRC})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
