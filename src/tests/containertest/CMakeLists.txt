#-------------------------------------------------------------------------------
# containertest
#-------------------------------------------------------------------------------

SET(containertest_src
	main.cc)

SOURCE_GROUP("" FILES ${containertest_src})
ADD_EXECUTABLE(containertest ${containertest_src})
TARGET_LINK_LIBRARIES(containertest core)
JARVIS_SETUP_TARGET(containertest Console)
SET_TARGET_PROPERTIES(containertest PROPERTIES FOLDER "JARVIS/tests")
