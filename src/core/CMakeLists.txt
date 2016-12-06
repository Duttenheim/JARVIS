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
	mem.h
	poolalloc.h
	ptr.h
	pqueue.h
	queue.h
	rand.h
	ref.h
	renderapplication.h
	renderapplication.cc
	singleton.h	
	typeinfo.h
	typeinfo.cc
)

SOURCE_GROUP("" FILES ${core})

SET(core_util
	util/allocator.h
	util/array.h
	util/map.h
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

SET(core_functional
	functional/function.h
)
SOURCE_GROUP("functional" FILES ${core_functional})

SET(core_network
	network/socket.h
	network/socket.cc
)
SOURCE_GROUP("network" FILES ${core_network})

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
	)
	SOURCE_GROUP("os" FILES ${core_os})
ELSEIF(APPLE)	
	SET(core_os
		apple/pch.h
		apple/applesocket.h
		apple/applesocket.cc
		apple/sysfunc.h
		apple/sysfunc.mm
	)
	SOURCE_GROUP("os" FILES ${core_os})

    FIND_LIBRARY(COCOA_FRAMEWORK Cocoa)

    SET(core_os_libs ${COCOA_FRAMEWORK})
ELSE()
	SET(core_os
		posix/pch.h
		posix/posixsocket.h
		posix/posixsocket.cc
	)
	SOURCE_GROUP("os" FILES ${core_os})
ENDIF()

ADD_LIBRARY(core STATIC ${core} ${core_util} ${core_threads} ${core_functional} ${core_math} ${core_os} ${core_io} ${core_network})
JARVIS_SETUP_TARGET(core)
TARGET_INCLUDE_DIRECTORIES(core PUBLIC ${JARVIS_SOURCE_DIR}/src/core)
TARGET_LINK_LIBRARIES(core ext ${core_os_libs})
