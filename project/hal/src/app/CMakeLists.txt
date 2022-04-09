project (HALTestApp)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories(HALTestApp ${CMAKE_SOURCE_DIR}/hal/include)
add_executable(HALTestApp hal_test.cpp)

target_link_libraries(HALTestApp LINK_PUBLIC HALCamera)
target_link_libraries(HALTestApp LINK_PUBLIC HALGPS)
target_link_libraries(HALTestApp PRIVATE ${CMAKE_DL_LIBS})
target_link_libraries(HALTestApp PRIVATE Threads::Threads)

