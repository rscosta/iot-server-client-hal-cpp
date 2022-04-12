project(IOTClient VERSION 1.0 DESCRIPTION "IOT Client Library")

file(GLOB SOURCES *.cpp)

add_library(IOTClient SHARED ${SOURCES})

target_link_libraries(IOTClient pthread)

set_target_properties(IOTClient PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER iot_client.h)

target_include_directories(IOTClient PRIVATE ${CMAKE_SOURCE_DIR}/iot_client_server/include)

install(TARGETS IOTClient
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

