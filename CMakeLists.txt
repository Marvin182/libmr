cmake_minimum_required(VERSION 3.2)

project(libmr CXX) # project name and programming languages (CXX = C++)

# make custom modules and scripts available to include() and find_package() commands
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_SOURCE_DIR}/cmake/Modules)

###
### CMake Policies
###
if(POLICY CMP0042)
	# Turn ON MACOSX_RPATH (with CMake 3.0 this became the default)
	# https://cmake.org/cmake/help/v3.0/policy/CMP0042.html
	cmake_policy(SET CMP0042 NEW)
endif()

# Throw error if we are not building out of source
include(RequireOutOfSourceBuild)

###
### CMake Policies
###
option(BUILD_WITH_QT "Build parts depending on Qt" ON)

###
### Build
###
if (NOT CMAKE_BUILD_TYPE)
	# default to Release
	set(CMAKE_BUILD_TYPE "Release")
	message(STATUS "No build type selected, default to Release. You can choose debug build by appending -DCMAKE_BUILD_TYPE=Debug to the cmake command.")
endif()

# put binaries in bin/ and lib/ subfolders instead of CMAKE_BINARY_DIR root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

###
### Sources
###
file(GLOB src_algo src/algo/*.cpp)
set(src_common src/common/pempek_assert.cpp src/common/random.cpp)
set(src_util src/util/Timer.cpp)
set(src_all ${src_common} ${src_util} src/version.cpp)

if (BUILD_WITH_QT)
	file(GLOB src_qt src/qt/*.cpp src/qt/*.h)
	set(src_qt ${src_qt} src/common/assert.cpp src/common/log.cpp)
	set(src_all ${src_all} ${src_qt})
endif()

###
### Targets
###
add_library(libmr SHARED ${src_all})
set_target_properties(libmr PROPERTIES OUTPUT_NAME mr CXX_STANDARD 14)

if (BUILD_WITH_QT)
	# Qt5 documentation on using CMake: http://doc.qt.io/qt-5/cmake-manual.html

	# Add Homebrew default install directory for qt5 formula
	set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} /usr/local/Cellar/qt5/5.7.0)

	# Instruct CMake to run moc automatically for sources.
	set(CMAKE_AUTOMOC ON)

	# Instruct CMake to run moc automatically when needed.
	find_package(Qt5Core 5.7.0 REQUIRED)
	find_package(Qt5Gui 5.7.0 REQUIRED)
	target_link_libraries(libmr Qt5::Core)
	target_link_libraries(libmr Qt5::Gui)
endif()

# Configure version.cpp to contain version information based on the repository history
add_custom_target(libmr_version_cpp ALL COMMAND ${CMAKE_COMMAND} -DSOURCE_DIR=${PROJECT_SOURCE_DIR} -P ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ConfigureVersionCppFromGit.cmake)
add_dependencies(libmr libmr_version_cpp)
