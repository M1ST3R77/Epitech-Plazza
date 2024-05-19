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
        src/Pizza/Manager/APizza.cpp
        src/Pizza/Manager/APizza.hpp
        src/Pizza/Margarita.cpp
        src/Pizza/Margarita.hpp
        src/Pizza/Regina.cpp
        src/Pizza/Regina.hpp
        src/Pizza/Americana.cpp
        src/Pizza/Americana.hpp
        src/Pizza/Fantasia.cpp
        src/Pizza/Fantasia.hpp
        src/Pizza/Manager/PizzaFactory.cpp
        src/Pizza/Manager/PizzaFactory.hpp
        src/Pizza/Manager/PizzaPacker.cpp
        src/Pizza/Manager/PizzaPacker.hpp
        src/Logger/Logger.cpp
        src/Logger/Logger.hpp
        src/ThreadPool/ThreadPool.cpp
        src/ThreadPool/ThreadPool.hpp
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
