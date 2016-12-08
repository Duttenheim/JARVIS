#-------------------------------------------------------------------------------
# nettest
#-------------------------------------------------------------------------------

SET(nettest_src
	main.cc)

SOURCE_GROUP("" FILES ${nettest_src})
ADD_EXECUTABLE(nettest ${nettest_src})
TARGET_LINK_LIBRARIES(nettest core)
JARVIS_SETUP_TARGET(nettest Console)
SET_TARGET_PROPERTIES(nettest PROPERTIES FOLDER "JARVIS/tests")
