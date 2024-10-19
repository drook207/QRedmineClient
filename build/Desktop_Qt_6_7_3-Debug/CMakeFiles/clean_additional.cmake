# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/QRedmineClient_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/QRedmineClient_autogen.dir/ParseCache.txt"
  "QRedmineClient_autogen"
  )
endif()
