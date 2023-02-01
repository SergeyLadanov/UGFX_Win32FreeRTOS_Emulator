cmake_minimum_required(VERSION 3.10)

# Put directory name to COMPONENT_NAME variable
get_filename_component(COMPONENT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
# Set component name
project(${COMPONENT_NAME})


# Файлы с исходым кодом
FILE(
    GLOB
    SOURCE_LIB 
    "Source/*.c"
    "Source/portable/MSVC-MingW/*.c"
    "Source/portable/MemMang/heap_5.c"
    "Common/Minimal/*.c"
    "ThirdParty/Template/*.c"
    )

# Add includes
include_directories(
    Config
    Source/portable/MSVC-MingW
    Source/include
    Common/include
    ThirdParty/Template/
)

# Creating static library
add_library(${COMPONENT_NAME} STATIC ${SOURCE_LIB})

target_compile_definitions(${COMPONENT_NAME} PUBLIC "-DprojCOVERAGE_TEST=1")
target_compile_definitions(${COMPONENT_NAME} PUBLIC "-D_WIN32_WINNT=0x0601")

add_compile_options(-O0 -g3 -Wall -Wextra -c -fmessage-length=0 -Wcast-qual)


target_link_libraries(${PROJECT_NAME} winmm)
