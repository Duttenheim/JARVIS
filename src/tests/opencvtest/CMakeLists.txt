#-------------------------------------------------------------------------------
# opencvtest
#-------------------------------------------------------------------------------

SET(target opencvtest)

SET(opencvtest_src
	main.cc)

IF (APPLE)
SET(OPENCV_INCLUDE /opt/local/include/)
SET(OPENCV_LIB libopencv_core.dylib)
LINK_DIRECTORIES(/opt/local/lib)
ENDIF()

SOURCE_GROUP("" FILES ${opencvtest_src})
ADD_EXECUTABLE(${target} ${opencvtest_src})
ADD_DEPENDENCIES(${target} core)
TARGET_INCLUDE_DIRECTORIES(${target} PUBLIC ${OPENCV_INCLUDE})
TARGET_LINK_LIBRARIES(${target} core ${OPENCV_LIB})
JARVIS_SETUP_TARGET(${target} Windows)
SET_TARGET_PROPERTIES(${target} PROPERTIES FOLDER "JARVIS/tests")
