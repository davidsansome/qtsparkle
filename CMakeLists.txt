cmake_minimum_required(VERSION 2.6)

find_package(Qt4 4.6.0 REQUIRED QtCore QtGui QtNetwork QtXml)
add_definitions(${QT_DEFINITIONS})
include(${QT_USE_FILE})

list(APPEND CMAKE_C_FLAGS -Wall)
list(APPEND CMAKE_CXX_FLAGS -Wall)

add_subdirectory(src)
add_subdirectory(exampleapp)
