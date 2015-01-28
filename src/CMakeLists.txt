function(add_public_header oldname newname)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${oldname}"
    "${CMAKE_BINARY_DIR}/include/qtsparkle${QT_SUFFIX}/${newname}"
    COPY_ONLY)
  install(FILES "${CMAKE_BINARY_DIR}/include/qtsparkle${QT_SUFFIX}/${newname}"
          DESTINATION include/qtsparkle${QT_SUFFIX})
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

add_library(qtsparkle
  ${SOURCES}
  ${TRANSLATION_TEMPLATE}
)

set_target_properties(qtsparkle
  PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    OUTPUT_NAME qtsparkle${QT_SUFFIX}
)

target_link_libraries(qtsparkle
  ${QT_LIBRARIES}
)

install(TARGETS qtsparkle
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)

