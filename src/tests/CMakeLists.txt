#-------------------------------------------------------------------------------
# tests
#-------------------------------------------------------------------------------

ADD_SUBDIRECTORY(testscrap)
ADD_SUBDIRECTORY(containertest)
ADD_SUBDIRECTORY(threadingtest)
ADD_SUBDIRECTORY(mathtest)
ADD_SUBDIRECTORY(windowtest)


IF (${J_BUILD_OPENCV})
	ADD_SUBDIRECTORY(opencvtest)
ENDIF()