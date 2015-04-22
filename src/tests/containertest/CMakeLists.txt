#-------------------------------------------------------------------------------
# containertest
#-------------------------------------------------------------------------------

SET(containertest_src
	main.cc)
	
ADD_EXECUTABLE(containertest ${containertest_src})
TARGET_LINK_LIBRARIES(containertest core)
JARVIS_SETUP_TARGET(containertest)
SET_TARGET_PROPERTIES(containertest PROPERTIES FOLDER "JARVIS/tests")