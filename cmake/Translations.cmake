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
