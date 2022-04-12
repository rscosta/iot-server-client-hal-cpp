project (IOTClientApp)

file(GLOB SOURCES *.cpp)

add_executable(IOTClientApp ${SOURCES})

include_directories(IOTClientApp ${CMAKE_SOURCE_DIR}/iot_client_server/include)

include_directories(IOTClientApp ${CMAKE_SOURCE_DIR}/hal/include)

include_directories(IOTClientApp ${CMAKE_SOURCE_DIR}/custom_json/include)

link_directories(${CMAKE_BINARY_DIR}/custom_json/src/lib)

link_directories(${CMAKE_BINARY_DIR}/hal/src/lib/temp_sensor)

target_link_libraries(IOTClientApp pthread)

target_link_libraries(IOTClientApp CustomJson)

target_link_libraries(IOTClientApp IOTClient)

target_link_libraries(IOTClientApp HALTempSensor)

target_link_libraries(IOTClientApp ${CMAKE_DL_LIBS})
