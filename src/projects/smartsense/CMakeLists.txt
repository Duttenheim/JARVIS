#-------------------------------------------------------------------------------
# smart sense
#-------------------------------------------------------------------------------

SET(target_name smartsense)
SET(${target_name}_src
	smartsenseapp.h
	smartsenseapp.cc
	imagestream.h
	imagestream.cc
    recognizer.h
    recognizer.cc
	main.cc)

SOURCE_GROUP("" FILES ${${target_name}_src})
ADD_EXECUTABLE(${target_name} ${${target_name}_src})
TARGET_LINK_LIBRARIES(${target_name} core)
JARVIS_SETUP_TARGET(${target_name})
SET_TARGET_PROPERTIES(${target_name} PROPERTIES FOLDER "JARVIS/projects")
