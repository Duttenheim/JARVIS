#-------------------------------------------------------------------------------
# JARVIS
#-------------------------------------------------------------------------------

set_property(GLOBAL PROPERTY USE_FOLDERS On)
CMAKE_MINIMUM_REQUIRED(VERSION 3.0.2)

PROJECT(JARVIS)

include(CMakeDependentOption)

IF(WIN32)
ADD_DEFINITIONS(-D__WIN32__)
ENDIF()

ADD_SUBDIRECTORY(src)