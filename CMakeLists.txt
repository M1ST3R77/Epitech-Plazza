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
        includes/Command.hpp
        includes/Utils.hpp
        src/Utils.cpp
        src/Kitchen/Kitchen.cpp
        src/Kitchen/Kitchen.hpp
        src/Process/ProcessPool.cpp
        src/Process/ProcessPool.hpp
        src/IPC/IPC.cpp
        src/IPC/IPC.hpp
        includes/IPizza.hpp
        src/Pizza/APizza.cpp
        src/Pizza/APizza.hpp
        src/Pizza/Margarita.cpp
        src/Pizza/Margarita.hpp
        src/Pizza/Regina.cpp
        src/Pizza/Regina.hpp
        src/Pizza/Americana.cpp
        src/Pizza/Americana.hpp
        src/Pizza/Fantasia.cpp
        src/Pizza/Fantasia.hpp
        src/Pizza/PizzaFactory.cpp
        src/Pizza/PizzaFactory.hpp
        src/Pizza/PizzaPacker.cpp
        src/Pizza/PizzaPacker.hpp
)

include_directories(includes)

add_executable(plazza ${SRC})

add_custom_command(TARGET plazza POST_BUILD
        COMMAND cp plazza ${PROJECT_SOURCE_DIR})
