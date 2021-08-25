cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

project(fggSerial C)

file(GLOB_RECURSE FGG_UART_SRC fggUART/src/*.c)
add_library(fggUART ${FGG_UART_SRC})
target_include_directories(fggUART PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/fggUART/include
)

option(FGG_SERIAL_BUILD_EXAMPLE OFF)
if (FGG_SERIAL_BUILD_EXAMPLE)

file(GLOB_RECURSE FGG_SERIAL_EXAMPLE_SRC fggSerialExample/src/*.c)
add_executable(fggSerialExample ${FGG_SERIAL_EXAMPLE_SRC})
target_include_directories(fggSerialExample PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/fggSerialExample/include
)
target_link_libraries(fggSerialExample PUBLIC
  fggUART
)
set_target_properties(fggSerialExample PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)

endif()

set_target_properties(fggUART PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)