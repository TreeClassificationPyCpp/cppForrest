# set precompiler defines
add_definitions(-DQT_DLL)
add_definitions(-DDECISIONTREE_LIB)
		
if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE)
endif()

## DecisionTree Includes##

set(SOURCE_FILES
	DecisionTree.cpp
	Node.cpp
	Tree.cpp
	TreeScalingParameter.cpp
	)

set(HEADER_FILES
	DecisionTree.h
	DecisionTree_global.h
	Node.h
	Tree.h
	TreeScalingParameter.h
	)

set(QT_MOC_HEADERS)




# add classes to MOC
foreach(headerFile ${HEADER_FILES} )
        file(STRINGS ${headerFile} var REGEX "Q_OBJECT")
        if(var)
		#message(${headerFile})
            list(APPEND QT_MOC_HEADERS ${headerFile})
        endif()
endforeach()
 
list(APPEND QT_MOC_SOURCES)
 
if (QT_MOC_HEADERS)
    qt5_wrap_cpp(QT_MOC_SOURCES ${QT_MOC_HEADERS})
	source_group("Generated Files" FILES ${QT_MOC_SOURCES})
endif()
  
add_library(DecisionTree STATIC ${SOURCE_FILES} ${HEADER_FILES} ${QT_MOC_SOURCES})

target_link_libraries(DecisionTree Qt5::Core 	${Boost_MATH_C99_LIBRARY}
                                       ${Boost_CONTAINER_LIBRARY}
                                       ${Boost_CHRONO_LIBRARY}
                                       ${Boost_SYSTEM_LIBRARY}
									   )
										

#target_link_libraries(	${PROJECT_NAME} debug  ${SPLINES_DEBUG_LIBRARIES})
#target_link_libraries(	${PROJECT_NAME} optimized   ${SPLINES_RELEASE_LIBRARIES})
#target_link_libraries(	${PROJECT_NAME} debug  ${SwallowingLib_DEBUG_LIBRARIES})
#target_link_libraries(	${PROJECT_NAME} optimized   ${SwallowingLib_RELEASE_LIBRARIES})		
target_link_libraries(	DecisionTree debug  ${CoreLib_DEBUG_LIBRARIES})
target_link_libraries(	DecisionTree optimized   ${CoreLib_RELEASE_LIBRARIES})
					   
target_include_directories(DecisionTree PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}/src
                            ${CMAKE_CURRENT_SOURCE_DIR}
							${CMAKE_CURRENT_BINARY_DIR}
                            ${Boost_INCLUDE_DIR}
							${CoreLib_INCLUDE_DIRS}
)

target_compile_definitions(DecisionTree PUBLIC BOOST_ALL_NO_LIB QT_NO_KEYWORDS)
set_target_properties(DecisionTree PROPERTIES DEBUG_POSTFIX d)
