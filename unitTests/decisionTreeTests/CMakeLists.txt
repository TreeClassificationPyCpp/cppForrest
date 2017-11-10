#project(DecisionTreeTests)


enable_testing()

 if(CMAKE_COMPILER_IS_GNUCXX)
   SET(ENABLE_CXX11 "-std=c++11")

   EXECUTE_PROCESS(COMMAND "${CMAKE_CXX_COMPILER} -dumpversion" OUTPUT_VARIABLE GCC_VERSION)
   if (GCC_VERSION VERSION_LESS 4.7)
      SET(ENABLE_CXX11 "-std=c++0x")
   endif()

   SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ENABLE_CXX11}")
endif()
                               

set(SOURCE_FILES
		
	tst_DecisionTree.cpp
			
	BoostTest.cpp
	
	)
	


set(HEADER_FILES

	BoostTest.h

	)






   
if (USE_PCH)

	activate_precompiled_headers("Pch.h" SRC_FILES)

endif() 
	


add_executable(DecisionTreeTests 
		${SOURCE_FILES}
		${HEADER_FILES} 
	)




add_test(NAME DecisionTreeTests COMMAND DecisionTreeTests)




include_directories(${BOOST_DIR})

include_directories(${CMAKE_SOURCE_DIR}/src)



target_link_libraries(DecisionTreeTests   
		gtest gmock_main
					 
                      )

if (MSVC)
target_link_libraries(DecisionTreeTests   debug  ${CMAKE_SOURCE_DIR}/lib/DecisionTree/Debug/DecisionTreed.lib)
target_link_libraries(DecisionTreeTests   optimized    ${CMAKE_SOURCE_DIR}/lib/DecisionTree/Release/DecisionTree.lib)
else(MSVC)
target_link_libraries(DecisionTreeTests   debug  ${CMAKE_SOURCE_DIR}/lib/DecisionTree/libDecisionTreed.a)
target_link_libraries(DecisionTreeTests   optimized    ${CMAKE_SOURCE_DIR}/lib/DecisionTree/libDecisionTree.a)
endif(MSVC)

add_dependencies(DecisionTreeTests   DecisionTree gtest gmock_main)



target_include_directories(DecisionTreeTests PUBLIC
					    ${CMAKE_SOURCE_DIR}/src
				
)

  
target_compile_definitions(DecisionTreeTests PUBLIC UNIT_TEST)


if(MSVC)

	set_target_properties(DecisionTreeTests PROPERTIES COMPILE_FLAGS "/Zm200 /bigobj")

endif()


add_custom_target(CopyTestData

    COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/treeClassifier_tree.txt  ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/treeClassifier_forrest.txt  ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/test_tree.txt  ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/test_forrest.txt  ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/data_tree.txt  ${CMAKE_BINARY_DIR}
	COMMAND ${CMAKE_COMMAND} -E copy_if_different  ${CMAKE_SOURCE_DIR}/unitTests/decisionTreeTests/data_forrest.txt  ${CMAKE_BINARY_DIR}

           )
   add_dependencies(DecisionTreeTests CopyTestData)



SET(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})