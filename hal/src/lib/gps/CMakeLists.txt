project(HALGPS VERSION 1.0 DESCRIPTION "HAL for Global Positioning System Library")
add_library(HALGPS SHARED hal_gps.cpp)

set_target_properties(HALGPS PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_gps.h)

target_include_directories(HALGPS PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALGPS
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

