#-------------------------------------------------------------------------------
# core
#-------------------------------------------------------------------------------

SET(core
    appargs.h
	application.h
	application.cc
	class.h
	config.h
	config.cc
	constness.h
	debug.h
	enum.h
	function.h
	mem.h
	poolalloc.h
	ptr.h
	rand.h
	ref.h
	renderapplication.h
	renderapplication.cc
	singleton.h	
	sysfunc.h
	typeinfo.h
	typeinfo.cc
	wrap.h
)

SOURCE_GROUP("" FILES ${core})

SET(core_util
	util/allocator.h
	util/array.h
	util/map.h
	util/prioqueue.h
	util/queue.h
	util/string.h
	util/timer.h
    util/tuple.h	
)
SOURCE_GROUP("util" FILES ${core_util})

SET(core_threads
	threads/thread.h
	threads/thread.cc
	threads/threading.h
	threads/threadpool.h
	threads/threadpool.cc
	threads/persistentthread.h
	threads/persistentthread.cc
)
SOURCE_GROUP("threads" FILES ${core_threads})

SET(core_network
	network/socket.h
)
SOURCE_GROUP("network" FILES ${core_network})

SET(interface_network
	interface/socket.h
	interface/socket.cc
)
SOURCE_GROUP("interface" FILES ${interface_network})

SET(core_math
	math/vec4.h
	math/vec3.h
	math/mat3.h
	math/mat4.h
	math/point.h
	math/vector.h
	math/point.h
)
SOURCE_GROUP("math" FILES ${core_math})

SET(core_io
	io/uri.h
	io/uri.cc
	io/assigns.h
    io/assigns.cc
)
SOURCE_GROUP("io" FILES ${core_io})

IF(WIN32)
	SET(core_os
		win32/pch.h
		win32/win32socket.h
		win32/win32socket.cc
		win32/win32sysfunc.h
		win32/win32sysfunc.cc
	)
	SOURCE_GROUP("os" FILES ${core_os})
ELSEIF(APPLE)	
	SET(core_os
		apple/pch.h
		apple/applesocket.h
		apple/applesocket.cc
		apple/applesysfunc.h
		apple/applesysfunc.mm
	)
	SOURCE_GROUP("os" FILES ${core_os})

    FIND_LIBRARY(COCOA_FRAMEWORK Cocoa)

    SET(core_os_libs ${COCOA_FRAMEWORK})
ELSEIF(ANDROID)
	SET(core_os
		android/pch.h
		posix/posixsocket.h
		posix/posixsocket.cc
		android/sysfunc.h
		android/sysfunc.cc
	)
	SOURCE_GROUP("os" files ${core_os})
ELSE()
	SET(core_os
		posix/pch.h
		posix/posixsocket.h
		posix/posixsocket.cc
		posix/sysfunc.h
		posix/sysfunc.cc
	)
	SOURCE_GROUP("os" FILES ${core_os})
ENDIF()

SET(OS_PLATFORM_LIBS "")
IF(WIN32)
	SET(OS_PLATFORM_LIBS "Ws2_32.lib")
ENDIF()

ADD_LIBRARY(core STATIC ${core} ${core_util} ${core_threads} ${core_math} ${core_os} ${core_io} ${core_network} ${interface_network})
JARVIS_SETUP_TARGET(core Library)
TARGET_INCLUDE_DIRECTORIES(core PUBLIC ${JARVIS_SOURCE_DIR}/src/core)
TARGET_LINK_LIBRARIES(core ext ${core_os_libs} ${OS_PLATFORM_LIBS})
