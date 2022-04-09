project(HALLightsSensor VERSION 1.0 DESCRIPTION "HAL Light Sensor Library")
add_library(HALLightsSensor SHARED hal_light_sensor.cpp)

set_target_properties(HALLightsSensor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_light_sensor.h)

target_include_directories(HALLightsSensor PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALLightsSensor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

