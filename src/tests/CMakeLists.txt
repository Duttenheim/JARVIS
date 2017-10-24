#-------------------------------------------------------------------------------
# tests
#-------------------------------------------------------------------------------

ADD_SUBDIRECTORY(testscrap)
ADD_SUBDIRECTORY(containertest)
ADD_SUBDIRECTORY(threadingtest)
ADD_SUBDIRECTORY(mathtest)
ADD_SUBDIRECTORY(windowtest)
ADD_SUBDIRECTORY(nettest)

ADD_SUBDIRECTORY(opencvtest)
IF (${J_BUILD_OPENCV})
ENDIF()
