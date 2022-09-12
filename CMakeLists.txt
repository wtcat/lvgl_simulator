cmake_minimum_required(VERSION 3.8)
project(lvgl_sim)
enable_language(C CXX)

set(TARGET_NAME ${PROJECT_NAME})
include (cmake/extensions.cmake)

if (POLICY CMP0076)
    cmake_policy(SET CMP0076 NEW)
endif(POLICY CMP0076)

# Select operation system
message(STATUS "OS Platform: ${CMAKE_SYSTEM_NAME}")
if (CMAKE_HOST_WIN32)
    enable_language(RC)
    set(WINDOWS TRUE)
    add_compile_options(/wd4819)
elseif (CMAKE_HOST_APPLE)
    set(MACOS TRUE)
elseif (CMAKE_HOST_UNIX)
    set(LINUX TRUE)
else ()
  message(FATAL_ERROR "Unknown operation system")
endif ()

# Find depend package
set(EXTRA_LIBS )
if (LINUX)
    include(FindPkgConfig)
    pkg_search_module(SDL2 REQUIRED sdl2)
    include_directories(
        ${SDL2_INCLUDE_DIR}
    )
  add_definitions(-include config.h)
  add_compile_options(-m32)
  list(APPEND EXTRA_LIBS pthread m)
elseif (WINDOWS)
    set(SDL_PATH sdl/SDL2/lib/x86)
    link_directories(${SDL_PATH})
    list(APPEND SDL2_LIBRARIES 
        SDL2
        SDL2main
    )
   if (NOT EXISTS ${PROJECT_BINARY_DIR}/SDL2.dll)
        file(COPY ${SDL_PATH}/SDL2.dll 
            DESTINATION ${PROJECT_BINARY_DIR})
   endif()
#    set(PREINCLUDE /FI"config.h")
#    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   ${PREINCLUDE}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PREINCLUDE}")
    add_compile_options(
        /utf-8
        /wd4996
    )
endif()

# Global compile options
include_directories(
  ${PROJECT_SOURCE_DIR}
  sdl/SDL2/include
  lvgl/src
  lv_drivers
)

set(CMAKE_C_STANDARD   11)
set(CMAKE_CXX_STANDARD 17)

# Generate executable file
add_executable(${TARGET_NAME} 
    main.cc 
#    backtrace.cc
    mtrace.c
)

add_subdirectory(thirdparty)

# LVGL Sources
static_library(lvgl)
file(GLOB_RECURSE LVGL_SOURCES lvgl/src/*.c)
target_sources(lvgl
	PRIVATE
	${LVGL_SOURCES}
)

# LVGL Demos
static_library(lvgl_demo)
file(GLOB_RECURSE LVGL_DEMO_SOURCES lvgl/demos/*.c)
target_sources(lvgl_demo
	PRIVATE
	${LVGL_DEMO_SOURCES}
)

#LVGL Drivers
static_library(lvgl_drv)
file(GLOB_RECURSE LVGL_DRV_SOURCES lv_drivers/*.c)
target_sources(lvgl_drv
	PRIVATE
	${LVGL_DRV_SOURCES}
)

# Link target
collect_link_libraries(libs ${TARGET_NAME})
if (LINUX)
  target_link_libraries(${TARGET_NAME} 
    -Wl,--start-group
    ${libs}
    -Wl,--end-group
    ${SDL2_LIBRARIES}
    ${EXTRA_LIBS}
  )
else()
  target_link_libraries(${TARGET_NAME} 
    ${libs}
    ${SDL2_LIBRARIES}
    ${EXTRA_LIBS}
  )
endif()