macro(make_lib name)
    file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/src/lib/${name}/*.cpp)

    add_library(${name} SHARED ${SOURCES})

    target_link_libraries(${name} pthread)

    install(TARGETS ${name} DESTINATION /usr/lib)
endmacro()

make_lib(iot_server)
make_lib(iot_client)



