#-------------------------------------------------------------------------------
# core
#-------------------------------------------------------------------------------

SET(core
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

IF(WIN32)
	SET(core_win32
		win32/pch.h
	)
	SOURCE_GROUP("core\\win32" FILES ${core_win32})
	
	SET(core_os ${core_win32})
ENDIF()

ADD_LIBRARY(core STATIC ${core} ${core_util} ${core_threads} ${core_functional} ${core_os})
JARVIS_SETUP_TARGET(core)
TARGET_INCLUDE_DIRECTORIES(core PUBLIC ${JARVIS_SOURCE_DIR}/src/core)
SET_TARGET_PROPERTIES(core PROPERTIES FOLDER "JARVIS")
