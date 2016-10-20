cmake_minimum_required(VERSION 3.2)

project(LibMrDemo CXX)

# We need the path to the directory with the CMakeLists.txt of libmr.
# You don't need to build libmr yourself!
set(LIBMR_DIR ${CMAKE_SOURCE_DIR}/..)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${LIBMR_DIR}/cmake)

# If you want to build libmr including classes that use Qt classes you have to make sure cmake can find a recent Qt version.
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /usr/local/Cellar/qt5/5.7.0)
# Otherwise just turn of the support.
set(BUILD_WITH_QT OFF CACHE BOOL "Build with classes using Qt.")

add_executable(demo main.cpp)
set_target_properties(demo PROPERTIES CXX_STANDARD 14)

# Add libmr as a target and link it.
add_subdirectory(${LIBMR_DIR}/ ${CMAKE_BINARY_DIR}/lib)
include_directories(${LIBMR_DIR}/include)
target_link_libraries(demo libmr)
