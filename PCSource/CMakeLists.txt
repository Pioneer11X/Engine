

cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(CEngine)

# add_subdirectory(Source)

# file(GLOB PC_SRC "Source/PC_Stuff/*.cpp" "Source/PC_Stuff/*.h")
# file(GLOB PC_Shader_SRC "Source/PC_Stuff/Shaders/*.vs" "Source/PC_Stuff/Shaders/*.frag")
# file(GLOB PS_SRC "Source/PS_Stuff/*.cpp" "Source/PS_Stuff/*.h")
# file(GLOB Shared_SRC "Source/SharedCode/*.cpp" "Source/SharedCode/*.h" "Source/Sharedcode/*.txt")

file(GLOB Source "Source/*.cpp" "Source/*.h")

file(GLOB GLM_Src
	"Source/glm/*"
)

# PC Specific Stuff.
IF(${CMAKE_TARGET_PS})

	# PS Specific Stuff.
	add_executable(CEngine ${PS_SRC})
	include_directories("Source/PS_Stuff/")

ELSE(${CMAKE_TARGET_PS})

	#PC Stuff
	add_executable(CEngine ${Source})

	source_group("Shaders" FILES ${PC_Shader_SRC})
	target_sources(CEngine PUBLIC ${PC_Shader_SRC})
	include_directories("Source/PC_Stuff/")

ENDIF(${CMAKE_TARGET_PS})

include_directories("Source/SharedStuff")

# Shared Stuff like the Libraries.

# source_group("Shared" FILES ${Shared_SRC})
# target_sources(CEngine PUBLIC ${Shared_SRC})

source_group("glm" FILES ${GLM_Src})
target_sources(CEngine PUBLIC ${GLM_Src})


add_definitions()


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

   # Mac OS X specific code
   SET(OperatingSystem "Mac OS X")

   # Use the homebrew installation location to make it behave well.
   include_directories("/usr/local/Cellar/glfw/3.2.1/include/")
   include_directories("/usr/local/Cellar/glew/2.0.0/include/")

   find_package(OpenGL)

   IF (OPENGL_FOUND)

   		include_directories(${OPENGL_INCLUDE_DIR})
   		target_link_libraries(CEngine ${OPENGL_LIBRARIES})

   ENDIF (OPENGL_FOUND)

   target_link_libraries(CEngine "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib")
   target_link_libraries(CEngine "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib")

   # You need to manually set the Working Directory. Similar to the VS_DEEBBUGER_WORKING_DIRECTORY.

ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(WIN32)
	
	# This if for Visual Studio 2015.

	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLFW/include/")
   	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/include/")

	find_package(OpenGL)

   	IF (OPENGL_FOUND)

   		include_directories(${OPENGL_INCLUDE_DIR})
   		target_link_libraries(CEngine ${OPENGL_LIBRARIES})

   	ENDIF (OPENGL_FOUND)

	# target_link_libraries(Engine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/lib/glew32.lib")
	target_link_libraries(CEngine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/lib/glew32s.lib")
	target_link_libraries(CEngine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLFW/lib/glfw3.lib")
	
	# set_target_properties(CEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/")


ENDIF(WIN32)

