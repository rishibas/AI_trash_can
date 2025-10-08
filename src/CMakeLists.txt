cmake_minimum_required(VERSION 3.21)
project(opencv_test CXX)

find_package(OpenCV REQUIRED)

file(GLOB MY_SOURCE src/*)

add_executable(${PROJECT_NAME} ${MY_SOURCE})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    ${OpenCV_LIBS}
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")

