cmake_minimum_required(VERSION 3.26)

set(PROJECT_NAME kursovaya_C++)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(SOURCES
        src/main.cpp
        src/PointersArray.cpp
        src/PointersList.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/include
)
