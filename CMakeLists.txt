cmake_minimum_required(VERSION 2.8)

PROJECT(Spider-Fish)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(SFML REQUIRED)


IF (WIN32)
    # Windows
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

SET(RESOURCES   ${CMAKE_CURRENT_SOURCE_DIR}/assets/background.jpg 
			    ${CMAKE_CURRENT_SOURCE_DIR}/assets/blur.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/colorize.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/edge.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/fisheye.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/nothing.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/pixelate.sfx
				${CMAKE_CURRENT_SOURCE_DIR}/assets/sansation.ttf
				${CMAKE_CURRENT_SOURCE_DIR}/assets/sprite.png
				${CMAKE_CURRENT_SOURCE_DIR}/assets/wave.jpg
				${CMAKE_CURRENT_SOURCE_DIR}/assets/wave.sfx)


SET (SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/Shader.cpp)
#SET (HEADERS include/resources.h)


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

#IF (WIN32)
#    set_target_properties(${PROJECT_NAME}
#        PROPERTIES
#            WIN32_EXECUTABLE TRUE)
#ENDIF (WIN32)


target_link_libraries(${PROJECT_NAME} 
    sfml-system 
    sfml-window
    sfml-network
    sfml-graphics
    sfml-audio
    ${EXTRA_LIBS})
