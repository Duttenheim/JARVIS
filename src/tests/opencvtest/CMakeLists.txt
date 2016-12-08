#-------------------------------------------------------------------------------
# opencvtest
#-------------------------------------------------------------------------------

SET(target opencvtest)

SET(opencvtest_src
	main.cc)

SOURCE_GROUP("" FILES ${opencvtest_src})
ADD_EXECUTABLE(${target} ${opencvtest_src})
ADD_DEPENDENCIES(${target} core opencv)
TARGET_LINK_LIBRARIES(${target} core opencv)
JARVIS_SETUP_TARGET(${target} Windows)
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "JARVIS/tests")
