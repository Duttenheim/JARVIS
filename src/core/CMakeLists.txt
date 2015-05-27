#-------------------------------------------------------------------------------
# core
#-------------------------------------------------------------------------------

SET(core
	application.h
	application.cc
	class.h
	config.h
	config.cc
	debug.h
	enum.h
	mem.h
	ptr.h
	pqueue.h
	queue.h
	rand.h
	ref.h
	singleton.h	
)

SOURCE_GROUP("core" FILES ${core})

SET(core_util
	util/allocator.h
	util/array.h
	util/map.h
	util/string.h
	util/timer.h
)
SOURCE_GROUP("core\\util" FILES ${core_util})

SET(core_threads
	threads/thread.h
	threads/thread.cc
	threads/threading.h
	threads/threadpool.h
	threads/threadpool.cc
	threads/persistentthread.h
	threads/persistentthread.cc
)
SOURCE_GROUP("core\\threads" FILES ${core_threads})

SET(core_functional
	functional/function.h
)
SOURCE_GROUP("core\\functional" FILES ${core_functional})

SET(core_network
	network/socket.h
	network/socket.cc
)
SOURCE_GROUP("core\\network" FILES ${core_network})

IF(WIN32)
	SET(core_os
		win32/pch.h
		win32/win32socket.h
		win32/win32socket.cc
	)
	SOURCE_GROUP("core\\os" FILES ${core_os})
ELSEIF(APPLE)	
	SET(core_os
		apple/pch.h
		apple/applesocket.h
		apple/applesocket.cc
	)
	SOURCE_GROUP("core\\os" FILES ${core_os})
ELSE()
	SET(core_os
		posix/pch.h
		posix/posixsocket.h
		posix/posixsocket.cc
	)
	SOURCE_GROUP("core\\os" FILES ${core_os})
ENDIF()

ADD_LIBRARY(core STATIC ${core} ${core_util} ${core_threads} ${core_functional} ${core_os} ${core_network})
JARVIS_SETUP_TARGET(core)
TARGET_INCLUDE_DIRECTORIES(core PUBLIC ${JARVIS_SOURCE_DIR}/src/core)
SET_TARGET_PROPERTIES(core PROPERTIES FOLDER "JARVIS")
