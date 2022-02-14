cmake_minimum_required(VERSION 3.4)
cmake_policy(SET CMP0048 NEW)

project(download LANGUAGES C)

find_package(CURL REQUIRED)

file(GLOB_RECURSE
        SOURCE_FILES
        main.c
        download.c
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

include_directories(
        ${CMAKE_SOURCE_DIR}
        ${CURL_INCLUDE_DIR}
        )

target_link_libraries( ${PROJECT_NAME}
        ${CURL_LIBRARY}
        )
