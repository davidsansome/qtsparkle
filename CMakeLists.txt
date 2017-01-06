cmake_minimum_required(VERSION 2.8.11)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)

include(cmake/Translations.cmake)

option(BUILD_WITH_QT4 "Build qtsparkle with Qt4" ON)
option(BUILD_STATIC "Static build" OFF)
if(BUILD_WITH_QT4)
  find_package(Qt4 REQUIRED QtCore QtGui QtNetwork QtXml)
  add_definitions(${QT_DEFINITIONS})
  include(${QT_USE_FILE})

  macro(qt_add_resources)
    qt4_add_resources(${ARGN})
  endmacro()

  set(QT_SUFFIX "")
else()
  find_package(Qt5 REQUIRED COMPONENTS Core Network Xml Widgets LinguistTools)
  set(QT_LUPDATE_EXECUTABLE ${Qt5_LUPDATE_EXECUTABLE})
  set(QT_LRELEASE_EXECUTABLE ${Qt5_LRELEASE_EXECUTABLE})

  macro(qt_add_resources)
    qt5_add_resources(${ARGN})
  endmacro()

  set(QT_LIBRARIES Qt5::Core Qt5::Network Qt5::Widgets)
  set(QT_SUFFIX "-qt5")
endif()


SET(CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} -Wall")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(src)
add_subdirectory(exampleapp)
