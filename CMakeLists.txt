# Root CMake file for QRedmineClient Author: Pascal Berndt
#
# ##############################################################################

cmake_minimum_required(VERSION 3.16)

if(${CMAKE_SOURCE_DIR} EQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "Insource builds are not allowed")
endif()

add_subdirectory(src)
add_subdirectory(test)
