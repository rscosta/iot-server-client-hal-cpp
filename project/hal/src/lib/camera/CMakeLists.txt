project(HALCamera VERSION 1.0 DESCRIPTION "HAL Camera Library")
add_library(HALCamera SHARED hal_camera.cpp)

set_target_properties(HALCamera PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_camera.h)

target_include_directories(HALCamera PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALCamera
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

