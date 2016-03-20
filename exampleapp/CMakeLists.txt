include_directories(${CMAKE_BINARY_DIR}/include)

set(SOURCES
  main.cpp
  mainwindow.cpp
)

add_executable(exampleapp
  ${SOURCES}
)

if(BUILD_STATIC AND WIN32)
  set(LIBS
    -lssl
    -lcrypto
    -lws2_32
  )
endif()

target_link_libraries(exampleapp
  qtsparkle
  ${QT_LIBRARIES}
  ${LIBS}
)
