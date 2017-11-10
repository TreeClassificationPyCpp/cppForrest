# set precompiler defines

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
	${CMAKE_SOURCE_DIR}/external/inih/ini.c
	${CMAKE_SOURCE_DIR}/external/inih/cpp/INIReader.cpp
	)

set(HEADER_FILES
	DecisionTree.h
	DecisionTree_global.h
	Node.h
	Tree.h
	TreeScalingParameter.h
	${CMAKE_SOURCE_DIR}/external/inih/ini.h
	${CMAKE_SOURCE_DIR}/external/inih/cpp/INIReader.h
	)



  
add_library(DecisionTree STATIC ${SOURCE_FILES} ${HEADER_FILES} )

target_link_libraries(DecisionTree  )

					   
target_include_directories(DecisionTree PUBLIC
                            ${CMAKE_SOURCE_DIR}/external/inih
							${CMAKE_SOURCE_DIR}/external/inih/cpp
                            ${CMAKE_CURRENT_SOURCE_DIR}
							${CMAKE_CURRENT_BINARY_DIR}
)


set_target_properties(DecisionTree PROPERTIES DEBUG_POSTFIX d)
