#-------------------------------------------------------------------------------
# testscrap
#-------------------------------------------------------------------------------

SET(testscrap_src
	main.cc)
	
ADD_EXECUTABLE(testscrap ${testscrap_src})
TARGET_LINK_LIBRARIES(testscrap core)
JARVIS_SETUP_TARGET(testscrap)
SET_TARGET_PROPERTIES(testscrap PROPERTIES FOLDER "JARVIS/tests")
