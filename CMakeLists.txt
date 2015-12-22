cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# get rid of Qt

find_package(OpenGL REQUIRED)
find_package(Qt5OpenGL REQUIRED)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

add_library(painter ${SOURCES} ${HEADERS} ${UI_HEADERS})
target_compile_features(painter PUBLIC cxx_variadic_templates)
target_link_libraries(painter ${OPENGL_LIBRARIES})
qt5_use_modules(painter OpenGL)
