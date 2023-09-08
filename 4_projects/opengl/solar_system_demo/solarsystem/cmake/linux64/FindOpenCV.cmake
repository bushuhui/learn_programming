# OPENCV2_LIBS the list of OpenCV 2.2 or greater libs (WIN32 MINGW compiler only)

IF(WIN32)

	FIND_PATH( OPENCV2_PATH include/opencv2/opencv.hpp
		PATHS
		$ENV{OPENCV_HOME}
		C:/OpenCV2.2/
		C:/OpenCV2.3/
		C:/OpenCV2.4/
		C:/Qt/OpenCV2.4/
	)
	
	if( OPENCV2_PATH )
		MESSAGE( STATUS "Looking for OpenCV2.2 or greater - found")
		MESSAGE( STATUS "OpenCV2.2 path: ${OPENCV2_PATH}" )
		SET ( OPENCV_FOUND 1 )
		SET( OPENCV_INCLUDES "${OPENCV2_PATH}/include")
		
		# test for 64 or 32 bit
		if( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			SET( BUILD_DIR ${OPENCV2_PATH}/build/x64 )
		else( CMAKE_SIZEOF_VOID_P EQUAL 8 )
			SET( BUILD_DIR ${OPENCV2_PATH}/build/x86 )
		endif( CMAKE_SIZEOF_VOID_P EQUAL 8 )
		
		# MINGW
		if(MINGW)
			SET(OPENCV2_LIB_PATH ${OPENCV2_PATH}/bin)
			file(GLOB OPENCV_LIBRARIES "${OPENCV2_LIB_PATH}/lib*.dll")
		endif(MINGW)
		
		# Visual Studio 9
		if(MSVC90)
			SET(OPENCV2_LIB_PATH ${BUILD_DIR}/vc9/lib/)
			file(GLOB OPENCV2_RELEASE_LIBS "${OPENCV2_LIB_PATH}*[0-9][0-9][0-9].lib")
			file(GLOB OPENCV2_DEBUG_LIBS "${OPENCV2_LIB_PATH}*[0-9][0-9][0-9]d.lib")
		endif(MSVC90)
		
		# Visual Studio 10
		if(MSVC10)
			SET(OPENCV2_LIB_PATH ${BUILD_DIR}/vc10/lib/)
			file(GLOB OPENCV2_RELEASE_LIBS "${OPENCV2_LIB_PATH}*[0-9][0-9][0-9].lib")
			file(GLOB OPENCV2_DEBUG_LIBS "${OPENCV2_LIB_PATH}*[0-9][0-9][0-9]d.lib")
		endif(MSVC10)

		# Set the includes
		SET(OPENCV2_INCLUDE_PATH ${OPENCV2_PATH}/build/include/opencv2 ${OPENCV2_PATH}/build/include)
		

	else( OPENCV2_PATH )
		message( STATUS "Looking for OpenCV2.2 or greater  - not found" )
		SET ( OPENCV2_FOUND 0 )
	endif( OPENCV2_PATH )

ELSE(WIN32) # Linux

        message("Using current FindOpenCV.cmake!")
	FIND_PATH( OPENCV_INCLUDE_DIR opencv2/opencv.hpp
	# installation selected by user
        /opt/opencv-2.4.9/include
        #$ENV{OPENCV_HOME}/include
	# system placed in /usr/local/include
        #/usr/local/include
	# system placed in /usr/include
        #/usr/include
	)
        set(OPENCV_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.9/include")
        MESSAGE( STATUS "OpenCV2.2 include path: ${OPENCV_INCLUDE_DIR}" )


        set(OPENCV_MODULES2FIND opencv_world)

	foreach (OPENCV_MODULE_NAME ${OPENCV_MODULES2FIND})
                FIND_LIBRARY(${OPENCV_MODULE_NAME}_LIBRARIES NAMES ${OPENCV_MODULE_NAME}
                        PATHS
                        ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.9/lib
                        #/usr/lib/x86_64-linux-gnu
                        #/usr/lib
                        #/usr/local/lib
                        #/opt/local/lib
                        #/sw/lib
			)
                if(${OPENCV_MODULE_NAME}_LIBRARIES)
			set(${OPENCV_MODULE_NAME}_INCLUDES ${OPENCV_INCLUDES})
			set(${OPENCV_MODULE_NAME}_FOUND 1)
			list(APPEND OPENCV_LIBRARIES ${${OPENCV_MODULE_NAME}_LIBRARIES})
		else(${OPENCV_MODULE_NAME}_LIBRARIES)
			message("Can't found module " ${OPENCV_MODULE_NAME})
		endif(${OPENCV_MODULE_NAME}_LIBRARIES)
	endforeach()
#        set(OPENCV_TOPDIR ${CMAKE_CURRENT_LIST_DIR}/opencv-2.4.9)
#        set(OPENCV_LIBRARIES ${OPENCV_TOPDIR}/lib/libopencv_world.so)
        
        #set(OPENCV_LIBRARIES ${OPENCV_LIBRARIES} -lswscale -lavutil -lavformat -lavcodec -ldc1394 -lgthread-2.0 -lfreetype -lfontconfig -lglib-2.0 -lgobject-2.0 -lpango-1.0 -lpangoft2-1.0 -lgio-2.0 -lgdk_pixbuf-2.0 -lcairo -latk-1.0 -lpangocairo-1.0 -lgdk-x11-2.0 -lgtk-x11-2.0 /usr/lib/x86_64-linux-gnu/libIlmThread.so /usr/lib/x86_64-linux-gnu/libHalf.so /usr/lib/x86_64-linux-gnu/libIex.so  /usr/lib/x86_64-linux-gnu/libImath.so /usr/lib/x86_64-linux-gnu/libjasper.so /usr/lib/x86_64-linux-gnu/libtiff.so /usr/lib/x86_64-linux-gnu/libjpeg.so -lrt -lpthread -lm -ldl -lstdc++)
	if( OPENCV_INCLUDE_DIR AND OPENCV_LIBRARIES)
		MESSAGE( STATUS "Looking for OpenCV2.2 or greater - found")
		MESSAGE( STATUS "OpenCV2.2 include path: ${OPENCV_INCLUDE_DIR}" )
		#MESSAGE( STATUS "OpenCV2.2 LIBS: ${OPENCV_LIBRARIES}" )
		SET ( OPENCV2_FOUND 1 )
		SET ( OPENCV_FOUND 1 )
	else(  OPENCV_INCLUDE_DIR AND OPENCV_LIBRARIES)
		message( STATUS "Looking for OpenCV2.2 or greater  - not found" )
		SET ( OPENCV2_FOUND 0 )
		SET ( OPENCV_FOUND 0 )
	endif(  OPENCV_INCLUDE_DIR AND OPENCV_LIBRARIES)

	
ENDIF(WIN32)

IF(OPENCV2_FOUND)
	  	set(OpenCV_INCLUDES ${OPENCV_INCLUDE_DIR})
	  	set(OpenCV_LIBRARIES ${OPENCV_LIBRARIES})
ENDIF(OPENCV2_FOUND)
