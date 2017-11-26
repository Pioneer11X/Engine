#This file should geenrate project files based on the Platform you are running it on.

#To generate a PS4 Project, set the option, CMAKE_PS4 to true when building. You have to manually add the ***** debugger everytime.

cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

project(Engine)

IF(${CMAKE_PS4})
    #PS4 Specific Stuff.
    file(GLOB PS_SRC "PS4Source/*.h" "PS4Source/*.cpp" "PS4Source/*.pssl" "PS4Source/*.sb" "PS4Source/*.hs" )
    
    add_executable(Engine ${PS_SRC})
    
    include_directories("PS4Source/sceFiles")
    
ELSE(${CMAKE_PS4})

    #PC Specific Stuff.
    file(GLOB_RECURSE PC_SRC 
    "PCSource/*.cpp" "PCSource/*.h" "PCSource/*.hpp" "PCSource/*.vs" "PCSource/*.frag"  
    )
    
    add_executable(Engine ${PC_SRC})
    
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

       # Mac OS X specific code
       SET(OperatingSystem "Mac OS X")

       # Use the homebrew installation location to make it behave well.
       include_directories("/usr/local/Cellar/glfw/3.2.1/include/")
       include_directories("/usr/local/Cellar/glew/2.0.0/include/")

       find_package(OpenGL)

       IF (OPENGL_FOUND)

            include_directories(${OPENGL_INCLUDE_DIR})
            target_link_libraries(Engine ${OPENGL_LIBRARIES})

       ENDIF (OPENGL_FOUND)

       target_link_libraries(Engine "/usr/local/Cellar/glew/2.0.0/lib/libGLEW.2.0.0.dylib")
       target_link_libraries(Engine "/usr/local/Cellar/glfw/3.2.1/lib/libglfw.3.2.dylib")

       # You need to manually set the Working Directory. Similar to the VS_DEEBBUGER_WORKING_DIRECTORY.

    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    IF(WIN32)

        # This if for Visual Studio 2015.
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLFW/include/")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/include/")

        find_package(OpenGL)

        IF (OPENGL_FOUND)

            include_directories(${OPENGL_INCLUDE_DIR})
            target_link_libraries(Engine ${OPENGL_LIBRARIES})

        ENDIF (OPENGL_FOUND)

        # target_link_libraries(Engine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/lib/glew32.lib")
        target_link_libraries(Engine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLEW/lib/glew32d.lib")
        target_link_libraries(Engine "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/_Win/GLFW/lib/glfw3.lib")

        # set_target_properties(Engine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Source/")


    ENDIF(WIN32)

ENDIF(${CMAKE_PS4})

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/SharedSource")
    
    