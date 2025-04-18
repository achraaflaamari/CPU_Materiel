cmake_minimum_required(VERSION 3.16)

project(CPU_FORMATION VERSION 1.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.0/mingw_64")
set(UI_FILES cmake-build-debug/CPU.ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt6_wrap_ui(WRAPPED_UI ${UI_FILES})

set(SOURCES main.cpp app_icon.rc)
add_executable(CPU_FORMATION WIN32 main.cpp ${WRAPPED_UI} ${SOURCES}
        DATA.cpp)
target_link_libraries(CPU_FORMATION Qt6::Widgets)
set_target_properties(CPU_FORMATION PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
