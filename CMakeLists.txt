cmake_minimum_required(VERSION 3.16)

project(QRedmineClient LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_library(
  QRedmineClient SHARED
  qredmineclient_global.h
  client.cpp
  client.h
  authentication.h
  authentication.cpp
  passwordauthentication.h
  passwordauthentication.cpp
  tokenauthentication.h
  tokenauthentication.cpp
  request.h
  request.cpp)

target_link_libraries(QRedmineClient PRIVATE Qt${QT_VERSION_MAJOR}::Core
											 Qt${QT_VERSION_MAJOR}::Network)

target_compile_definitions(QRedmineClient PRIVATE QREDMINECLIENT_LIBRARY)
