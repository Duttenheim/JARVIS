#-------------------------------------------------------------------------------
# smart sense
#-------------------------------------------------------------------------------

SET(target_name smartsense)
SET(${target_name}_src
    movementtracker.h
    movementtracker.cc
	smartsenseapp.h
	smartsenseapp.cc
	imagestream.h
	imagestream.cc
    objectrecognizer.h
    objectrecognizer.cc
    recognizer.h
    recognizer.cc
	main.cc)

SOURCE_GROUP("" FILES ${${target_name}_src})

IF(${J_PLATFORM_ANDROID})
	SET(ANDROID_THIS_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})
	ADD_LIBRARY(${target_name} SHARED ${${target_name}_src})
	ANDROID_CREATE_APK(${target_name} "${CMAKE_BINARY_DIR}/apk" ${target_name}.so "./" "Data")
ELSE()
	ADD_EXECUTABLE(${target_name} ${${target_name}_src})
ENDIF()

TARGET_LINK_LIBRARIES(${target_name} core)
JARVIS_SETUP_TARGET(${target_name} Windows)
SET_TARGET_PROPERTIES(${target_name} PROPERTIES FOLDER "JARVIS/projects")
