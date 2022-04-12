project (IOTServerApp)

file(GLOB SOURCES *.cpp)

add_executable(IOTServerApp ${SOURCES})

include_directories(IOTServerApp ${CMAKE_SOURCE_DIR}/iot_client_server/include)

include_directories(IOTServerApp ${CMAKE_SOURCE_DIR}/custom_json/include)

link_directories(${CMAKE_BINARY_DIR}/custom_json/src/lib)

target_link_libraries(IOTServerApp pthread)

target_link_libraries(IOTServerApp IOTServer)

target_link_libraries(IOTServerApp CustomJson)

