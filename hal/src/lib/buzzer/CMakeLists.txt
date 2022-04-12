project(HALBuzzer VERSION 1.0 DESCRIPTION "HAL for Buzzer Library")
add_library(HALBuzzer SHARED hal_buzzer.cpp)

set_target_properties(HALBuzzer PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER hal_buzzer.h)

target_include_directories(HALBuzzer PRIVATE ${CMAKE_SOURCE_DIR}/hal/include)

install(TARGETS HALBuzzer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

