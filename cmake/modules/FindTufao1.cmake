# Find Tufao script.

set(TUFAO_ROOT "$ENV{TUFAO_DIR}" CACHE PATH "TUFAO root directory.")

# Look for headers.
find_path(TUFAO_INCLUDE_DIRS
          NAMES httpsserver.h
          HINTS $ENV{TUFAO_DIR}
          PATHS ${TUFAO_ROOT}
          PATH_SUFFIXES include/tufao-1/Tufao)


# List of all SDK libraries.
set(TUFAO_LIB_NAMES
	tufao1)

# Find optimized libraries.
set(TUFAO_LIB)
foreach(LIB ${TUFAO_LIB_NAMES})
	set(LIB_PATH ${LIB}-NOTFOUND)
	find_library(LIB_PATH
				 NAMES ${LIB}
				 HINTS $ENV{TUFAO_DIR}
				 PATHS ${TUFAO_ROOT}
				 PATH_SUFFIXES	lib
								bin)
				 
	list(APPEND TUFAO_LIB ${LIB_PATH})
endforeach()

message(STATUS "TUFAO [DEBUG]: TUFAO_INCLUDE_DIRS = ${TUFAO_LIB_NAMES}.    ${LIB_PATH}")

# Find debug libraries (may be missing in your distribution).
set(TUFAO_LIBD)
foreach(LIB ${TUFAO_LIB_NAMES})
	set(LIB_PATH ${LIB}-NOTFOUND)
	find_library(LIB_PATH
				 NAMES ${LIB}d
				 HINTS $ENV{TUFAO_DIR}
				 PATHS ${TUFAO_ROOT}
				 PATH_SUFFIXES	lib
								bin)
				 
	list(APPEND TUFAO_LIBD ${LIB_PATH})
endforeach()

#message(STATUS "TUFAO [DEBUG]: TUFAO_LIB = ${TUFAO_LIB}.")
#message(STATUS "TUFAO [DEBUG]: TUFAO_LIBD = ${TUFAO_LIBD}.")

# Support the REQUIRED and QUIET arguments, and set TUFAO_FOUND if found.
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TUFAO DEFAULT_MSG 
                                  TUFAO_LIB
                                  TUFAO_INCLUDE_DIRS)
								  
set(TUFAO_LIBRARIES)
								  
if(TUFAO_FOUND)
	if(TUFAO_LIB)
		foreach(LIB ${TUFAO_LIB})
			list(APPEND TUFAO_LIBRARIES optimized ${LIB})
		endforeach()
	endif()
	if(TUFAO_LIBD)
		foreach(LIB ${TUFAO_LIBD})
			list(APPEND TUFAO_LIBRARIES debug ${LIB})
		endforeach()
		message(STATUS "TUFAO [INFO]: Debug libraries are available.")
	elseif(TUFAO_LIB)
		foreach(LIB ${TUFAO_LIB})
			list(APPEND TUFAO_LIBRARIES debug ${LIB})
		endforeach()
		message(STATUS "TUFAO [WARN]: Debug libraries are NOT available.")
	endif()
	message(STATUS "TUFAO [INFO]: Found TUFAO in ${TUFAO_ROOT}.")
else()
	message(STATUS "TUFAO [WARN]: TUFAO was NOT found.")
endif(TUFAO_FOUND)

#message(STATUS "TUFAO [DEBUG]: TUFAO_LIBRARIES = ${TUFAO_LIBRARIES}.")

if(NOT TUFAO_FOUND)
    message(FATAL_ERROR "Must provide tufao install directory")
endif()

# Don't show in GUI
mark_as_advanced(
	TUFAO_INCLUDE_DIRS
	TUFAO_LIBRARIES
	TUFAO_LIB_NAMES
	TUFAO_LIB_NAMESD
	TUFAO_LIB 
	TUFAO_LIBD
	LIB_PATH
)
