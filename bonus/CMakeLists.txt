cmake_minimum_required(VERSION 3.27)
project(bonus_plazza)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra)

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
        bonus_plazza
)

set(SRC src/Main.cpp
        src/Shell/Shell.hpp
        src/Shell/Shell.cpp
        src/Exceptions/Exceptions.hpp
        src/Exceptions/Exceptions.cpp
        src/Utils.cpp
        src/NCurses.cpp
        src/NPlazza.cpp
)

include_directories(includes)

add_executable(bonus_plazza ${SRC})

target_link_libraries(bonus_plazza PRIVATE ncurses)

target_link_directories(bonus_plazza PRIVATE
        includes/)

add_custom_command(TARGET bonus_plazza POST_BUILD
        COMMAND cp bonus_plazza ${PROJECT_SOURCE_DIR})
