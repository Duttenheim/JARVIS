#-------------------------------------------------------------------------------
# testscrap
#-------------------------------------------------------------------------------

SET(testscrap_src
	main.cc)

SOURCE_GROUP("" FILES ${testscrap_src})
ADD_EXECUTABLE(testscrap ${testscrap_src})
TARGET_LINK_LIBRARIES(testscrap core)
JARVIS_SETUP_TARGET(testscrap Console)
SET_TARGET_PROPERTIES(testscrap PROPERTIES FOLDER "JARVIS/tests")
