cmake_minimum_required(VERSION 3.13.0)

project(parsing
	LANGUAGES "CXX"
)

include(GNUInstallDirs)
include(FindPkgConfig)
include(FindBoost)

# The binary itself
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		main.cpp
)

# Version for the library symlinks
set_target_properties(${PROJECT_NAME}
	PROPERTIES
		CXX_STANDARD 17
)


# Libraries
#pkg_check_modules(LIBCLSP REQUIRED libclsp)

pkg_check_modules(rapidjson REQUIRED IMPORTED_TARGET RapidJSON)



include_directories(../../include)

set(LIBCLSP_INCLUDE_DIRS
		../../include)

find_library(LIBCLSP libclsp.dylib ../../cmake-build-release)

# Header path
target_include_directories(${PROJECT_NAME}
	PUBLIC
		${LIBCLSP_INCLUDE_DIRS}
		Boost::headers

	INTERFACE
		PkgConfig::rapidjson
)

# Linking
target_link_libraries(${PROJECT_NAME}
	PUBLIC
		${LIBCLSP}
		Boost::headers

	INTERFACE
		PkgConfig::rapidjson
)

# Other flags (without this rapidjson can't use std::string)
target_compile_options(${PROJECT_NAME}
	PUBLIC
		-DRAPIDJSON_HAS_STDSTRING=1
)
