function(add_public_header oldname newname)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${oldname}"
    "${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}${QT_SUFFIX}/${newname}"
    COPYONLY)
  install(FILES "${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}${QT_SUFFIX}/${newname}"
          DESTINATION include/${PROJECT_NAME}${QT_SUFFIX})
endfunction(add_public_header)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCES
  appcast.cpp
  common.cpp
  compareversions.cpp
  followredirects.cpp
  uicontroller.cpp
  updatechecker.cpp
  updatedialog.cpp
  updater.cpp
)

add_public_header(updater.h Updater)

add_translation_template(TRANSLATION_TEMPLATE
  ${CMAKE_CURRENT_SOURCE_DIR}/translations.ts
  ${SOURCES}
)

compile_translations(SOURCES
  "../translations" "qtsparkle_translations.qrc" "/qtsparkle/translations"
  "af"
  "br"
  "ca"
  "cs"
  "da_DK"
  "da"
  "de"
  "el"
  "es_AR"
  "es"
  "et"
  "eu"
  "fa"
  "fi"
  "fr"
  "hr"
  "hu"
  "it"
  "ja"
  "ka"
  "lt"
  "nl"
  "pl"
  "pt_BR"
  "pt"
  "ro"
  "ru"
  "sk"
  "sl"
  "tr_TR"
  "tr"
  "uk"
  "uz"
  "vi"
  "zh_CN"
  "zh_TW"
)

add_library(${PROJECT_NAME}
  ${SOURCES}
  ${TRANSLATION_TEMPLATE}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  CMAKE_CXX_STANDARD 17
  CMAKE_CXX_STANDARD_REQUIRED ON
  AUTOMOC ON
  AUTOUIC ON
  OUTPUT_NAME ${PROJECT_NAME}${QT_SUFFIX}
  PUBLIC_HEADER Updater
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(BUILD_SHARED_LIBS)
  target_compile_definitions(${PROJECT_NAME} PRIVATE QTSPARKLE_BUILD) # dllexport
else()
  target_compile_definitions(${PROJECT_NAME} PUBLIC QTSPARKLE_STATIC) # suppress dllimport
endif()

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
)
