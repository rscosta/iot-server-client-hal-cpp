project(HALIRObstacleSensor VERSION 1.0 DESCRIPTION "HAL IR Obstacle Sensor Library")
add_library(HALIRObstacleSensor SHARED hal_ir_obstacle_sensor.cpp)

set_target_properties(HALIRObstacleSensor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_ir_obstacle_sensor.h)

target_include_directories(HALIRObstacleSensor PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALIRObstacleSensor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

