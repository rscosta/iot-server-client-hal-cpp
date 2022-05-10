project(IOTServer VERSION 1.0 DESCRIPTION "IOT Server Library")

file(GLOB SOURCES *.cpp)

add_library(IOTServer SHARED ${SOURCES})

set_target_properties(IOTServer PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER iot_server.h)

target_include_directories(IOTServer PRIVATE ${CMAKE_SOURCE_DIR}/iot_client_server/include)

link_directories(${CMAKE_BINARY_DIR}/hal/src/lib/temp_sensor)

target_link_libraries(IOTServer pthread)

install(TARGETS IOTServer
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

