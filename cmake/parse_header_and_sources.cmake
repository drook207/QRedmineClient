# Macros to parse header and source files from a directorie

macro(Parse_headers result path)
  if(${path} STREQUAL "")
    message(WARNING "Empty path! Could not parse header files!")
    return()
  endif()
  set(__files)
  file(
    GLOB_RECURSE __files
    RELATIVE ${path}
    CONFIGURE_DEPENDS "*.h*")

  set(${result} ${__files})
endmacro()

macro(Parse_sources result path)
  if(${path} STREQUAL "")
    message(WARNING "Empty path! Could not parse source files!")
    return()
  endif()
  set(__files)
  file(
    GLOB_RECURSE __files
    RELATIVE ${path}
    CONFIGURE_DEPENDS "*.c*")
  set(${result} ${__files})
endmacro()

function(install_headers target headers)
  list(LENGTH ${headers} __lenght)

  if(${__lenght} LESS_EQUAL 1)
    message(WARNING "Install_headers: Empty header list!")
  endif()

  if(${target} STREQUAL "")
    message(WARNING "No module provided!")
  endif()
  message(
    DEBUG
    "Install_headers: Try to parse install paths for module ${target} from ${headers}"
  )
  foreach(__header IN LISTS ${headers})
    message(DEBUG "Install_headers: ${__header}")
    get_filename_component(__dir ${__header} DIRECTORY)
    message(DEBUG
            "Install_headers: Directory to install the header is: ${__dir}.")
    install(FILES ${__header}
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${target}/${__dir})
  endforeach()
endfunction(install_headers)
