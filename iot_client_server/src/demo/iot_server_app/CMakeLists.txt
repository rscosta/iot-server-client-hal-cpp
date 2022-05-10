project (IOTServerApp)

file(GLOB SOURCES *.cpp)

add_executable(IOTServerApp ${SOURCES})

include_directories(IOTServerApp ${CMAKE_SOURCE_DIR}/iot_client_server/include)

target_link_libraries(IOTServerApp pthread)

target_link_libraries(IOTServerApp IOTServer)

