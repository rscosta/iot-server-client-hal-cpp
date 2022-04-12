project(CustomJson VERSION 1.0 DESCRIPTION "Custom Json Parser and Serializer Library")
add_library(CustomJson SHARED custom_json.cpp)

set_target_properties(CustomJson PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER custom_json.h)

target_include_directories(CustomJson PRIVATE ${CMAKE_SOURCE_DIR}/custom_json/include)

install(TARGETS CustomJson
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

