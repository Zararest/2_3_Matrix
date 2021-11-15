cmake_minimum_required(VERSION 2.8)
find_package(Boost 1.40 COMPONENTS program_options REQUIRED)

add_executable(Matrix src/main.cpp  src/headers/Matrix.hpp)

add_executable(Matrix_test src/test.cpp  src/headers/Matrix.hpp)

target_link_libraries(Matrix_test Boost::program_options)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)