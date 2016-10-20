cmake_minimum_required(VERSION 3.2)

set(version_cpp ${SOURCE_DIR}/src/version.cpp)
set(version_cpp_in ${SOURCE_DIR}/src/version.cpp.in)
set(version_cpp_tmp ${CMAKE_CURRENT_BINARY_DIR}/version.cpp.tmp)

find_package(Git)
if (NOT GIT_FOUND)
	message(SEND_ERROR "Git not found, building without Git version info!")
endif()

# default values
set(git_version_major 0)
set(git_version_minor 1)
set(git_version_revision 0)
set(git_version_stage_name "alpha")
set(git_version_stage_number 1)
set(git_version_build 1)
set(git_version_commit "abcdef")
set(git_version_branch "")

execute_process(COMMAND ${GIT_EXECUTABLE} status
	WORKING_DIRECTORY ${SOURCE_DIR}
	RESULT_VARIABLE git_result
	OUTPUT_QUIET ERROR_QUIET)
if (git_result EQUAL 0)
	# tag version from latest tag
	execute_process(COMMAND ${GIT_EXECUTABLE} describe --abbrev=0 --tags
		WORKING_DIRECTORY ${SOURCE_DIR}
		RESULT_VARIABLE git_result
		OUTPUT_VARIABLE git_describe
		OUTPUT_STRIP_TRAILING_WHITESPACE
		ERROR_QUIET)
	if (git_result EQUAL 0)
		string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.?([0-9]*)-?(a|b|c|alpha|beta|rc|)([0-9]*)" dummy ${git_describe})
		if (dummy)
			set(git_version_major ${CMAKE_MATCH_1})
			set(git_version_minor ${CMAKE_MATCH_2})
			if (CMAKE_MATCH_3)
				set(git_version_revision ${CMAKE_MATCH_3})
			endif()
			set(git_version_stage_name ${CMAKE_MATCH_4})
			if (CMAKE_MATCH_5)
				set(git_version_stage_number ${CMAKE_MATCH_5})
			endif()
		else()
			message(WARNING "Could not parse version from git, using defaults, (git describe=${git_describe})")
		endif()
	else()
		message(WARNING "Latest tag is not a valid version tag.")
	endif()

	# Use number of ancestor commits as build number
	execute_process(COMMAND ${GIT_EXECUTABLE} rev-list HEAD --count
		WORKING_DIRECTORY ${SOURCE_DIR}
		OUTPUT_VARIABLE git_version_build
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	# Use more reliable way to get commit ID (parsing above could fail)
	execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
		WORKING_DIRECTORY ${SOURCE_DIR}
		OUTPUT_VARIABLE git_version_commit
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	# Get branch name
	execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
		WORKING_DIRECTORY ${SOURCE_DIR}
		OUTPUT_VARIABLE git_version_branch
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	# Print debug info
	message(STATUS "Building with git version info: ${git_describe} (branch: ${git_version_branch}, commit: ${git_version_commit}, build: ${git_version_build})")
else()
	message(WARNING "Git found, but working directory ${SOURCE_DIR} is not a Git repository, building without git version info! (git response: ${git_result})")
endif()

# Configure version file.
configure_file(${version_cpp_in} ${version_cpp_tmp})
execute_process(COMMAND ${CMAKE_COMMAND} -E copy_if_different ${version_cpp_tmp} ${version_cpp})
