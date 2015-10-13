#-------------------------------------------------------------------------------
# mathtest
#-------------------------------------------------------------------------------

SET(mathtest_src
	main.cc)

SOURCE_GROUP("" FILES ${mathtest_src})
ADD_EXECUTABLE(mathtest ${mathtest_src})
TARGET_LINK_LIBRARIES(mathtest core)
JARVIS_SETUP_TARGET(mathtest)
SET_TARGET_PROPERTIES(mathtest PROPERTIES FOLDER "JARVIS/tests")
