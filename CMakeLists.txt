cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(ShSerial C)

file(GLOB_RECURSE SH_SERIAL_SRC ShSerial/src/*.c)
add_library(ShSerial ${SH_SERIAL_SRC})
target_include_directories(ShSerial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ShSerial/include
)

option(SH_SERIAL_BUILD_EXAMPLE OFF)
if (SH_SERIAL_BUILD_EXAMPLE)

file(GLOB_RECURSE SH_SERIAL_EXAMPLE_SRC ShSerialExample/src/*.c)
add_executable(ShSerialExample ${SH_SERIAL_EXAMPLE_SRC})
target_include_directories(ShSerialExample PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/ShSerialExample/include
)
target_link_libraries(ShSerialExample PUBLIC
  ShSerial
)
set_target_properties(ShSerialExample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

endif()

set_target_properties(ShSerial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)