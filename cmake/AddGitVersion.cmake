# JRTk CMake Build Scripts
# Copyright (C) 2016 Marvin Ritter

# If possible get some version information from git and pass it via definitions to the compiler
# Source code should not depend the definitions being available!
find_package(Git)
if (GIT_FOUND)
	execute_process(COMMAND ${GIT_EXECUTABLE} describe --tags --always
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		RESULT_VARIABLE git_result
		OUTPUT_VARIABLE git_version
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	if (git_result EQUAL 0)
		execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			OUTPUT_VARIABLE git_branch
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			OUTPUT_VARIABLE git_commit_hash
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		message(STATUS "Building with git version info: ${git_version} (branch: ${git_branch})")
		add_definitions("-DGIT_BRANCH=\"${git_branch}\"") # branch name (e. g. develop or feature-cool-new-stuff)
		add_definitions("-DGIT_COMMIT_HASH=\"${git_commit_hash}\"") # short commit hash (e. g. ade1d9f)
		add_definitions("-DGIT_VERSION=\"${git_version}\"") # version string including last tag and commit hash
	else()
		message(WARNING "Git found, but working directory ${PROJECT_SOURCE_DIR} is not a Git repository, building without git version info! (git_result: ${git_result})")
	endif()
else()
	message(WARNING "Git not found, building without Git version info!")
endif()