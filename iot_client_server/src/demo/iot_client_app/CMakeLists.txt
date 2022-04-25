function (make_exe name file_name hal_lib_name)

    file(GLOB SOURCES ${file_name}.cpp)

    add_executable(${name} ${SOURCES})

    include_directories(${name} ${CMAKE_SOURCE_DIR}/iot_client_server/include)

    include_directories(${name} ${CMAKE_SOURCE_DIR}/hal/include)

    include_directories(${name} ${CMAKE_SOURCE_DIR}/custom_json/include)

    link_directories(${CMAKE_BINARY_DIR}/custom_json/src/lib)

    link_directories(${CMAKE_BINARY_DIR}/hal/src/lib/temp_sensor)

    target_link_libraries(${name} pthread)

    target_link_libraries(${name} CustomJson)

    target_link_libraries(${name} IOTClient)

    target_link_libraries(${name} ${hal_lib_name})

    target_link_libraries(${name} ${CMAKE_DL_LIBS})
endfunction()

# IOT Client Apps
make_exe(PubIotClientTempApp pub_iot_client_temperature_app HALTempSensor )
make_exe(PubIotClientAccelGyroApp pub_iot_client_accel_gyro_app HALAccelGyroSensor )
