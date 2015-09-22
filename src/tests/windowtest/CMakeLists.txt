#-------------------------------------------------------------------------------
# windowtest
#-------------------------------------------------------------------------------

SET(windowtest_src
	main.cc
	windowapp.h
	windowapp.cc)

SOURCE_GROUP("" FILES ${windowtest_src})
	
ADD_EXECUTABLE(windowtest ${windowtest_src})
TARGET_LINK_LIBRARIES(windowtest core render)
JARVIS_SETUP_TARGET(windowtest)
SET_TARGET_PROPERTIES(windowtest PROPERTIES FOLDER "JARVIS/tests")
