project(qtsparkle)

cmake_minimum_required(VERSION 2.8.11)
cmake_policy(SET CMP0020 NEW)
cmake_policy(SET CMP0043 NEW)

include(cmake/Translations.cmake)

option(BUILD_WITH_QT4 "Build qtsparkle with Qt 4" OFF)
option(BUILD_WITH_QT5 "Build qtsparkle with Qt 5" OFF)
option(BUILD_WITH_QT6 "Build qtsparkle with Qt 6" OFF)

if (NOT BUILD_WITH_QT4 AND NOT BUILD_WITH_QT5 AND NOT BUILD_WITH_QT6)
  set(BUILD_WITH_QT5 ON)
endif()

option(BUILD_STATIC "Static build" OFF)
if(BUILD_WITH_QT4)
  find_package(Qt4 REQUIRED QtCore QtGui QtNetwork QtXml)
  add_definitions(${QT_DEFINITIONS})
  include(${QT_USE_FILE})

  macro(qt_add_resources)
    qt4_add_resources(${ARGN})
  endmacro()

  set(QT_SUFFIX "")
  message("- Building with Qt 4")

elseif(BUILD_WITH_QT5)
  find_package(Qt5 REQUIRED COMPONENTS Core Network Widgets LinguistTools)
  set(QT_LUPDATE_EXECUTABLE ${Qt5_LUPDATE_EXECUTABLE})
  set(QT_LRELEASE_EXECUTABLE ${Qt5_LRELEASE_EXECUTABLE})

  macro(qt_add_resources)
    qt5_add_resources(${ARGN})
  endmacro()

  set(QT_LIBRARIES Qt5::Core Qt5::Network Qt5::Widgets)
  set(QT_SUFFIX "-qt5")
  message("- Building with Qt 5")

elseif(BUILD_WITH_QT6)
  find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets LinguistTools)
  set(QT_LUPDATE_EXECUTABLE Qt6::lupdate)
  set(QT_LRELEASE_EXECUTABLE Qt6::lrelease)

  macro(qt_add_resources)
    qt6_add_resources(${ARGN})
  endmacro()

  set(QT_LIBRARIES Qt6::Core Qt6::Network Qt6::Widgets)
  set(QT_SUFFIX "-qt6")
  message("- Building with Qt 6")
else()
  message(FATAL_ERROR "You need to set either BUILD_WITH_QT4, BUILD_WITH_QT5 or BUILD_WITH_QT6.")
endif()


SET(CMAKE_C_FLAGS    "${CMAKE_C_FLAGS} -Wall")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall")

add_subdirectory(src)
add_subdirectory(exampleapp)
