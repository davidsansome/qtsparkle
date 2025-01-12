include_directories(${CMAKE_BINARY_DIR}/include)

set(SOURCES
  main.cpp
  mainwindow.cpp
)

add_executable(exampleapp
  ${SOURCES}
)

target_link_libraries(exampleapp
  ${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${LIBS}
)

if(WIN32 AND BUILD_STATIC_LIBS)
  target_link_libraries(exampleapp
    -lssl
    -lcrypto
    -lws2_32
  )
endif()
