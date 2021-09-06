cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(fggSerial C)

file(GLOB_RECURSE FGG_SERIAL_SRC fggSerial/src/*.c)
add_library(fggSerial ${FGG_SERIAL_SRC})
target_include_directories(fggSerial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/fggSerial/include
)

option(FGG_SERIAL_BUILD_EXAMPLE OFF)
if (FGG_SERIAL_BUILD_EXAMPLE)

file(GLOB_RECURSE FGG_SERIAL_EXAMPLE_SRC fggSerialExample/src/*.c)
add_executable(fggSerialExample ${FGG_SERIAL_EXAMPLE_SRC})
target_include_directories(fggSerialExample PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/fggSerialExample/include
)
target_link_libraries(fggSerialExample PUBLIC
  fggSerial
)
set_target_properties(fggSerialExample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

endif()

set_target_properties(fggSerial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)