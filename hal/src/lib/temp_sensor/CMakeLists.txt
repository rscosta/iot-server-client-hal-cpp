project(HALTempSensor VERSION 1.0 DESCRIPTION "HAL Temperature Sensor Library")
add_library(HALTempSensor SHARED hal_temp_sensor.cpp)

set_target_properties(HALTempSensor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_temp_sensor.h)

target_include_directories(HALTempSensor PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALTempSensor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

