project(Illuminator)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(. SRC_LIST)
add_executable(${PROJECT_NAME} ${SRC_LIST})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

if(UNIX)
    target_link_libraries(${PROJECT_NAME} m)
endif()
