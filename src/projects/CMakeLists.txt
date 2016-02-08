#-------------------------------------------------------------------------------
# projects
#-------------------------------------------------------------------------------

FILE(GLOB alldirs ./*)
foreach(dir ${alldirs})
        if(IS_DIRECTORY ${dir})
		if(EXISTS ${dir}/CMakeLists.txt)
               add_subdirectory(${dir})
            	endif()			
        endif()
endforeach()