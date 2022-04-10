project(Json VERSION 1.0 DESCRIPTION "Json Parser and Serializer Library")
add_library(Json SHARED json.cpp)

set_target_properties(Json PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER json.h)

target_include_directories(Json PRIVATE ${CMAKE_SOURCE_DIR}/json/include)

install(TARGETS Json
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

