#-------------------------------------------------------------------------------
# testscrap
#-------------------------------------------------------------------------------

SET(testscrap_head
)

SET(testscrap_cc
	main.cc)
	
ADD_EXECUTABLE(testscrap ${testscrap_head} ${testscrap_cc})
TARGET_LINK_LIBRARIES(testscrap core)

SET_TARGET_PROPERTIES(testscrap PROPERTIES FOLDER "JARVIS/tests")