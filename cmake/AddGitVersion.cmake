# JRTk CMake Build Scripts
# Copyright (C) 2016 Marvin Ritter

# If possible get some version information from git and pass it via definitions to the compiler
# Source code should not depend the definitions being available!
macro(add_git_version target)
	find_package(Git)
	if (GIT_FOUND)
		execute_process(COMMAND ${GIT_EXECUTABLE} describe --always --long --tags
			WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
			RESULT_VARIABLE git_result
			OUTPUT_VARIABLE git_describe
			OUTPUT_STRIP_TRAILING_WHITESPACE)
		string(REGEX MATCH "([0-9]+)\\.([0-9]+)\\.([0-9]+)-?(a[0-9]|b[0-9]|c[0-9]|alpha[0-9]|beta[0-9]|rc[0-9]|)-[0-9]+-([a-z0-9]+)" dummy ${git_describe})
		if (git_result EQUAL 0)
			if (dummy)
				set(git_version_major ${CMAKE_MATCH_1})
				set(git_version_minor ${CMAKE_MATCH_2})
				set(git_version_revision ${CMAKE_MATCH_3})
				set(git_version_stage ${CMAKE_MATCH_4})
				set(git_commit_id ${CMAKE_MATCH_5})
			else()
				message(WARNING "Could not parse version from git, using defaults, (git describe=${git_describe})")
				set(git_version_major 0)
				set(git_version_minor 1)
				set(git_version_revision 0)
				set(git_version_stage "alpha")
				set(git_commit_id "abdcef")
			endif()
			execute_process(COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				OUTPUT_VARIABLE git_branch
				OUTPUT_STRIP_TRAILING_WHITESPACE)
			execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%h
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				OUTPUT_VARIABLE git_commit_hash
				OUTPUT_STRIP_TRAILING_WHITESPACE)
			execute_process(COMMAND ${GIT_EXECUTABLE} rev-list HEAD --count
				WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
				OUTPUT_VARIABLE git_commit_count
				OUTPUT_STRIP_TRAILING_WHITESPACE)
			message(STATUS "Building with git version info: ${git_version} (branch: ${git_branch})")
			target_compile_definitions(${target} PRIVATE "-DGIT_BRANCH=\"${git_branch}\"") # branch name (e. g. develop or feature-cool-new-stuff)
			target_compile_definitions(${target} PRIVATE "-DGIT_COMMIT_HASH=\"${git_commit_hash}\"") # short commit hash (e. g. ade1d9f)
			target_compile_definitions(${target} PRIVATE "-DGIT_VERSION=\"${git_version}\"") # version string including last tag and commit hash
		else()
			message(WARNING "Git found, but working directory ${PROJECT_SOURCE_DIR} is not a Git repository, building without git version info! (git_result: ${git_result})")
		endif()
	else()
		message(WARNING "Git not found, building without Git version info!")
	endif()
endmacro()

