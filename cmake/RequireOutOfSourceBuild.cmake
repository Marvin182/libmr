# JRTk CMake Build Scripts
# Copyright (C) 2016 Marvin Ritter

if ("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not permitted. Please, make a separate folder for building:\nmkdir build; cd build; cmake ..\nBefore that, remove the files already created:\nrm -rf CMakeCache.txt CMakeFiles\n")
endif()