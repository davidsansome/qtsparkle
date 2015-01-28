macro(add_translation_template outfiles template)
  # Make relative filenames for all source files
  set(add_translation_template_sources)
  foreach(_filename ${ARGN})
    get_filename_component(_absolute_filename ${_filename} ABSOLUTE)
    file(RELATIVE_PATH _relative_filename ${CMAKE_CURRENT_SOURCE_DIR} ${_absolute_filename})
    list(APPEND add_translation_template_sources ${_relative_filename})
  endforeach(_filename)

  add_custom_command(
    OUTPUT ${template}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND ${QT_LUPDATE_EXECUTABLE}
      ${ARGN}
      -ts ${template}
    DEPENDS ${ARGN}
  )

  list(APPEND ${outfiles} ${template})
endmacro(add_translation_template)


macro(compile_translations outfiles ts_dir qrc_name qrc_dir)
  set(qrc_filepath "${CMAKE_CURRENT_BINARY_DIR}/${qrc_name}")
  file(WRITE ${qrc_filepath} "<RCC><qresource prefix=\"${qrc_dir}\">")

  foreach(lang ${ARGN})
    set(ts_filename "${lang}.ts")
    set(ts_filepath "${CMAKE_CURRENT_SOURCE_DIR}/${ts_dir}/${ts_filename}")
    set(qm_filename "${lang}.qm")
    set(qm_filepath "${CMAKE_CURRENT_BINARY_DIR}/${qm_filename}")

    # Convert the .ts to .qm
    add_custom_command(
      OUTPUT ${qm_filepath}
      COMMAND ${QT_LRELEASE_EXECUTABLE} ARGS
        -silent
        ${ts_filepath}
        -qm ${qm_filepath}
      DEPENDS ${ts_filepath}
    )

    list(APPEND ${outfiles} ${qm_filepath})

    # Add the .qm to the .qrc
    file(APPEND ${qrc_filepath} "<file>${lang}.qm</file>")
  endforeach()

  file(APPEND ${qrc_filepath} "</qresource></RCC>")
  qt_add_resources(${outfiles} ${qrc_filepath})
endmacro()
