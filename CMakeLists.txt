cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(shSerial C)

file(GLOB_RECURSE SH_SERIAL_SRC shSerial/src/*.c)
add_library(shSerial ${SH_SERIAL_SRC})
target_include_directories(shSerial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/shSerial/include
)

option(SH_SERIAL_BUILD_EXAMPLE OFF)
if (SH_SERIAL_BUILD_EXAMPLE)

file(GLOB_RECURSE SH_SERIAL_EXAMPLE_SRC shSerialExample/src/*.c)
add_executable(shSerialExample ${SH_SERIAL_EXAMPLE_SRC})
target_include_directories(shSerialExample PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/shSerialExample/include
)
target_link_libraries(shSerialExample PUBLIC
  shSerial
)
set_target_properties(shSerialExample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

endif()

set_target_properties(shSerial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)