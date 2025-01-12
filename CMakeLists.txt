cmake_minimum_required(VERSION 3.13)
project(qtsparkle)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
endif()
if(POLICY CMP0043)
  cmake_policy(SET CMP0043 NEW)
endif()

include(CMakePackageConfigHelpers)
include(cmake/Translations.cmake)

option(BUILD_STATIC_LIBS "Static build" OFF)
option(BUILD_SHARED_LIBS "Shared build" ON)

option(BUILD_WITH_QT5 "Build qtsparkle with Qt 5" OFF)
option(BUILD_WITH_QT6 "Build qtsparkle with Qt 6" OFF)

if(NOT MSVC)
  add_compile_options(-Wall)
endif()

if(BUILD_WITH_QT5)
  set(QT_VERSION_MAJOR 5)
elseif(BUILD_WITH_QT6)
  set(QT_VERSION_MAJOR 6)
endif()

if(NOT QT_VERSION_MAJOR)
  message(FATAL_ERROR "You need to set either BUILD_WITH_QT5, BUILD_WITH_QT6 or QT_VERSION_MAJOR.")
endif()

find_package(Qt${QT_VERSION_MAJOR} REQUIRED Core Network Widgets LinguistTools)
set(QT_LIBRARIES Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::Widgets)
set(QT_LUPDATE_EXECUTABLE Qt${QT_VERSION_MAJOR}::lupdate)
set(QT_LRELEASE_EXECUTABLE Qt${QT_VERSION_MAJOR}::lrelease)
set(QT_SUFFIX "-qt${QT_VERSION_MAJOR}")
add_definitions(${QT_DEFINITIONS})

if(QT_VERSION_MAJOR EQUAL 5 AND Qt5Core_VERSION VERSION_LESS 5.15.0)
  macro(qt_add_resources)
    qt5_add_resources(${ARGN})
  endmacro()
endif()

message("- Building with Qt ${QT_VERSION_MAJOR}")

add_subdirectory(src)
add_subdirectory(exampleapp)

install(EXPORT ${PROJECT_NAME}${QT_SUFFIX}Targets
  NAMESPACE ${PROJECT_NAME}${QT_SUFFIX}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}${QT_SUFFIX}
)

configure_package_config_file(${PROJECT_NAME}Config.cmake.in ${PROJECT_NAME}${QT_SUFFIX}Config.cmake INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}${QT_SUFFIX})

install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}${QT_SUFFIX}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FRAMEWORK DESTINATION ${FRAMEWORK_INSTALL_DIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}${QT_SUFFIX}Config.cmake DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}${QT_SUFFIX})
