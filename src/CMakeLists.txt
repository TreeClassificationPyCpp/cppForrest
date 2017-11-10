# set precompiler defines

add_definitions(-DDECISIONTREE_LIB)
		
if(MSVC)
    add_definitions(-DUNICODE -D_UNICODE )
endif()

if(CMAKE_COMPILER_IS_GNUCXX)
   SET(ENABLE_CXX11 "-std=c++11")

   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
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
