find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

include(${CMAKE_SOURCE_DIR}/cmake/parse_header_and_sources.cmake)

parse_headers(HEADERS ${CMAKE_CURRENT_LIST_DIR})
parse_sources(SOURCES ${CMAKE_CURRENT_LIST_DIR})

add_library(QRedmineClient SHARED ${HEADERS} ${SOURCES})

target_link_libraries(QRedmineClient PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                             Qt${QT_VERSION_MAJOR}::Network)

target_compile_definitions(QRedmineClient PRIVATE QREDMINECLIENT_LIBRARY)
