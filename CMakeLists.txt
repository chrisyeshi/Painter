cmake_minimum_required(VERSION 2.8.11)

find_package(OpenGL REQUIRED)
find_package(Qt5OpenGL REQUIRED)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_library(painter ${SOURCES} ${HEADERS} ${UI_HEADERS})
qt5_use_modules(painter OpenGL)
target_link_libraries(painter ${OPENGL_LIBRARIES})
