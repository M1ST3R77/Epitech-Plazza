cmake_minimum_required(VERSION 3.27)
project(plazza)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        plazza
)

set(SRC src/Main.cpp
        src/Shell/Shell.hpp
        src/Shell/Shell.cpp
        src/Exceptions/Exceptions.hpp
        src/Exceptions/Exceptions.cpp
        src/Parsing/Parsing.cpp
        src/Parsing/Parsing.hpp
        src/Utils.cpp
        src/Process/Process.cpp
        src/Process/Process.hpp
        src/Kitchen/Kitchen.cpp
        src/Kitchen/Kitchen.hpp
)

include_directories(includes)

add_executable(plazza ${SRC})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
