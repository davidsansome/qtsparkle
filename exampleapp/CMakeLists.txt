include_directories(${CMAKE_BINARY_DIR}/include)

set(SOURCES
  main.cpp
  mainwindow.cpp
)

add_executable(exampleapp
  ${SOURCES}
)

target_link_libraries(exampleapp
  ${QT_LIBRARIES}
  qtsparkle
)
