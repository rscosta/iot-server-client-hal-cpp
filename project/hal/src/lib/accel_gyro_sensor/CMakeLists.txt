project(HALAccelGyroSensor VERSION 1.0 DESCRIPTION "HAL Accelerometer & Gyroscope Sensor Library")
add_library(HALAccelGyroSensor SHARED hal_accel_gyro_sensor.cpp)

set_target_properties(HALAccelGyroSensor PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_accel_gyro_sensor.h)

target_include_directories(HALAccelGyroSensor PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALAccelGyroSensor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

