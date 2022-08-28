target_include_directories(common_interface
  INTERFACE
  ${CMAKE_CURRENT_SOURCE_DIR}/SDL2/include/
)

#add_library(sdl2 STATIC IMPORTED GLOBAL)
#set_property(TARGET sdl2 PROPERTY
#  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2.lib"
#)

#add_library(sdl2main STATIC IMPORTED GLOBAL)
#set_property(TARGET sdl2main PROPERTY
#  IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/lib/x86/SDL2main.lib"
#)
