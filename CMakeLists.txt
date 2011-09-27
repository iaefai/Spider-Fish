# On Windows:  c:\Users\drakej\source\build-Spider-Fish>cmake -G "NMake Makefiles" -D SFMLDIR:String="C:\Program Files\SFML" ..\Spider-Fish
cmake_minimum_required(VERSION 2.8)

PROJECT(Spider-Fish)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SFML REQUIRED)


IF (WIN32)
    # Windows
	
	link_directories(${SFML_INCLUDE_DIR}/../lib)
	
	set(RESOURCE_HANDLER ${CMAKE_CURRENT_SOURCE_DIR}/src/windows/resources.cpp)
#	link_directories(${FIND_SFML_LIB_PATHS})
ELSEIF(APPLE)
        # Mac
        SET(RESOURCE_HANDLER ${CMAKE_CURRENT_SOURCE_DIR}/src/mac/resources.mm)
        SET(MACOSX_BUNDLE_GUI_IDENTIFER "com.iaefai.Spider-Fish")
        SET(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
        if (NOT CMAKE_OSX_ARCHITECTURES)
            set(CMAKE_OSX_ARCHITECTURES "i386;x86_64"
                CACHE STRING "Build architectures for OSX" FORCE)
        endif()
        
        if(EXISTS /Developer/SDKs/MacOSX10.7.sdk)
            set(CMAKE_OSX_SYSROOT "/Developer/SDKs/MacOSX10.7.sdk"
                CACHE STRING "Defaults to 10.7" FORCE)
        else()
            # use default SDK
        endif()           
    
        find_library(COCOA_LIB  Cocoa)
        
        SET(EXTRA_LIBS ${COCOA_LIB} ${OPENGL_LIBRARIES})
ELSE()
        # Linux // Assumed??
ENDIF()

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include})

include_directories(${SFML_INCLUDE_DIR})

SET(RESOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/assets/vertex.sfx
			    ${CMAKE_CURRENT_SOURCE_DIR}/assets/fragment.sfx)


#SET (SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp)
#SET (HEADERS include/resources.h)

#SET (CMAKE_CXX_FLAGS "-std=c++0x")
SET (SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Triangle.cpp
			${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp)

add_executable(${PROJECT_NAME} ${SOURCES} ${RESOURCE_HANDLER})

IF (APPLE)

    set_target_properties(${PROJECT_NAME} 
        PROPERTIES
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/src/mac/Spider-Fish-Info.plist
            MACOSX_BUNDLE  TRUE)      
    
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
    	COMMAND echo copying resources... 
    	#${RESOURCES}
    	COMMAND mkdir -p ./${PROJECT_NAME}.app/Contents/Resources
    	COMMAND cp ${RESOURCES} ./${PROJECT_NAME}.app/Contents/Resources				
    )
#    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD COMMAND echo ${PROJECT_NAME}.app/Contents/Resources)
    
    
ENDIF (APPLE)

IF (WIN32)
    set_target_properties(${PROJECT_NAME}
        PROPERTIES
            WIN32_EXECUTABLE FALSE)


	set(EXTRA_LIBS sfml-main ${OPENGL_LIBRARIES})
	# note we can add stuff to ADDITIONAL_MAKE_CLEAN_FILES 
	string(COMPARE EQUAL ${CMAKE_GENERATOR} "NMake Makefiles" NMAKE)
	if (NMAKE)
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND echo copying dlls...
			COMMAND copy ${SFML_INCLUDE_DIR}\\..\\bin\\*.dll .
			COMMAND echo copying resources... from ${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND -mkdir resources 
			COMMAND copy \"${CMAKE_CURRENT_SOURCE_DIR}\\assets\\*.*\" resources)
	else ()
		add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
			COMMAND echo copying dlls...
			COMMAND copy ${SFML_INCLUDE_DIR}\\..\\bin\\*.dll .
			COMMAND echo copying resources... from ${CMAKE_CURRENT_SOURCE_DIR}
			# Visual Studio does not support the '-' to ignore errors
			COMMAND rmdir /s /q resources
			COMMAND mkdir resources 
			COMMAND copy \"${CMAKE_CURRENT_SOURCE_DIR}\\assets\\*.*\" resources)
	endif (NMAKE)
ENDIF (WIN32)

#if (APPLE)
target_link_libraries(${PROJECT_NAME} 
    sfml-system 
    sfml-window
    sfml-network
    sfml-graphics
    sfml-audio
    ${EXTRA_LIBS})
#endif (APPLE)
