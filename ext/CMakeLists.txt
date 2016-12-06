ADD_LIBRARY(ext INTERFACE)

IF (${J_PLATFORM_ANDROID})
	INCLUDE(android-cmake/Apk.cmake)
	INCLUDE(android-cmake/android.toolchain.cmake)
	INCLUDE(android-cmake/AndroidNdkGdb.cmake)
	INCLUDE(android-cmake/AndroidNdkModules.cmake)
ENDIF()

LIST(APPEND ext_subdirs "opencv")
ADD_SUBDIRECTORY(opencv)

IF(${J_RENDERER_GL4})
	ADD_SUBDIRECTORY(glfw_ext)
	ADD_SUBDIRECTORY(glew_ext)
	LIST(APPEND ext_subdirs "glfw_ext" "glew_ext")
ENDIF()

#TARGET_INCLUDE_DIRECTORIES(ext INTERFACE ${ext_subdirs})
TARGET_LINK_LIBRARIES(ext INTERFACE ${ext_subdirs})
