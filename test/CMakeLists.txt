include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.2
  GIT_PROGRESS TRUE)

FetchContent_MakeAvailable(googletest)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(unit_tests main.cpp)

target_link_libraries(unit_tests PRIVATE gtest_main Qt${QT_VERSION_MAJOR}::Core
                                         Qt${QT_VERSION_MAJOR}::Network)
