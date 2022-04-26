function (make_pub_exe name file_name hal_lib_name)

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

function (make_sub_exe name file_name)

    file(GLOB SOURCES ${file_name}.cpp)

    add_executable(${name} ${SOURCES})

    include_directories(${name} ${CMAKE_SOURCE_DIR}/iot_client_server/include)

    include_directories(${name} ${CMAKE_SOURCE_DIR}/custom_json/include)

    link_directories(${CMAKE_BINARY_DIR}/custom_json/src/lib)

    target_link_libraries(${name} pthread)

    target_link_libraries(${name} CustomJson)

    target_link_libraries(${name} IOTClient)

    target_link_libraries(${name} ${CMAKE_DL_LIBS})
endfunction()


# IOT Client Apps (Publishers)
make_pub_exe(PubIotClientTempApp pub_iot_client_temperature_app HALTempSensor )
make_pub_exe(PubIotClientAccelGyroApp pub_iot_client_accel_gyro_app HALAccelGyroSensor )

# IOT Client Apps (Subscribers)
make_sub_exe(SubIotClientListenOnePubApp sub_listen_one_pub_app )
make_sub_exe(SubIotClientListenTwoPubsApp sub_listen_two_pubs_app )
