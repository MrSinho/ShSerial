cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(ShSerial C)

add_library(shserial ShSerial/src/shserial/shSerial.c)
target_include_directories(shserial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ShSerial/include
)
set_target_properties(shserial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)


option(SH_SERIAL_BUILD_EXAMPLE OFF)
if (SH_SERIAL_BUILD_EXAMPLE)

add_executable(shserialexample ShSerialExample/src/shSerialExample.c)
target_link_libraries(shserialexample PUBLIC shserial)
set_target_properties(shserialexample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

endif()
