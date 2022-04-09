cmake_minimum_required(VERSION 3.9)

project(HAL)

add_subdirectory (src/lib/temp_sensor)
add_subdirectory (src/lib/buzzer)
add_subdirectory (src/lib/gps)
add_subdirectory (src/lib/ir_obstacle_sensor)
add_subdirectory (src/lib/light_sensor)
add_subdirectory (src/lib/rgb_led)
add_subdirectory (src/lib/rtc)
add_subdirectory (src/lib/accel_gyro_sensor)
add_subdirectory (src/lib/camera)
add_subdirectory (src/app)









