cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(ShSerial C)

add_library(ShSerial ShSerial/src/shserial/shSerial.c)
target_include_directories(ShSerial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ShSerial/include
)

option(SH_SERIAL_BUILD_EXAMPLE OFF)
if (SH_SERIAL_BUILD_EXAMPLE)

add_executable(ShSerialExample ShSerialExample/src/shSerialExample.c)
target_link_libraries(ShSerialExample PUBLIC ShSerial)
set_target_properties(ShSerialExample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
endif()

set_target_properties(ShSerial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)