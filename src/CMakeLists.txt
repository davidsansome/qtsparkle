function(add_public_header oldname newname)
  configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/${oldname}"
    "${CMAKE_BINARY_DIR}/include/qtsparkle/${newname}"
    COPY_ONLY)
  install(FILES "${CMAKE_BINARY_DIR}/include/qtsparkle/${newname}"
          DESTINATION include/qtsparkle)
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

set(MOC_SOURCES
  followredirects.h
  uicontroller.h
  updatechecker.h
  updatedialog.h
  updater.h
)

set(UI_SOURCES
  updatedialog.ui
)

add_public_header(updater.h Updater)

qt4_wrap_cpp(MOC ${MOC_SOURCES})
qt4_wrap_ui(UIC ${UI_SOURCES})

add_translation_template(TRANSLATION_TEMPLATE
  ${CMAKE_CURRENT_SOURCE_DIR}/translations.ts
  ${SOURCES} ${MOC_SOURCES} ${UI_SOURCES}
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
  ${MOC}
  ${UIC}
  ${TRANSLATION_TEMPLATE}
)

target_link_libraries(qtsparkle
  ${QT_LIBRARIES}
)

install(TARGETS qtsparkle
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION bin
  RUNTIME DESTINATION bin
)

