#-------------------------------------------------------------------------------
# threadingtest
#-------------------------------------------------------------------------------

SET(threadingtest_src
	main.cc)

SOURCE_GROUP("" FILES ${threadingtest_src})
ADD_EXECUTABLE(threadingtest ${threadingtest_src})
TARGET_LINK_LIBRARIES(threadingtest core)
JARVIS_SETUP_TARGET(threadingtest)
SET_TARGET_PROPERTIES(threadingtest PROPERTIES FOLDER "JARVIS/tests")