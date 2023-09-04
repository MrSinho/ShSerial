cmake_minimum_required(VERSION 3.0)
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)



project(shserial C)



#||||       ||||
#||||LIBRARY||||
#||||       ||||
function(build_shserial)
add_library(shserial shserial/src/shserial/shSerial.c)
target_include_directories(shserial PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/shserial/include
)
set_target_properties(shserial PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
endfunction()



#||||                 ||||
#||||COMPILER SPECIFIC||||
#||||                 ||||
if(MSVC)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()



#||||       ||||
#||||EXAMPLE||||
#||||       ||||
function(build_shserial_logger)
add_executable(shserial-logger logger/src/logger.c)
target_link_libraries(shserial-logger PUBLIC shserial)
set_target_properties(shserial-logger PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)  
endfunction()



#||||     ||||
#||||FLAGS||||
#||||     ||||
option(SH_SERIAL_BUILD_LOGGER OFF)



#||||    ||||
#||||MAIN||||
#||||    ||||
function(main)
build_shserial()
if (SH_SERIAL_BUILD_LOGGER)
  build_shserial_logger()
endif()
endfunction()



main()
