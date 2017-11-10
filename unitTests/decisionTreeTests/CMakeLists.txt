#project(DecisionTreeTests)


enable_testing()

 
                               

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


target_link_libraries(DecisionTreeTests   debug  ${CMAKE_SOURCE_DIR}/lib/DecisionTree/Debug/DecisionTreed.lib)

target_link_libraries(DecisionTreeTests   optimized    ${CMAKE_SOURCE_DIR}/lib/DecisionTree/Release/DecisionTree.lib)

add_dependencies(DecisionTreeTests   DecisionTree gtest gmock_main)



target_include_directories(DecisionTreeTests PUBLIC
					    ${CMAKE_SOURCE_DIR}/src
				
)

  
target_compile_definitions(DecisionTreeTests PUBLIC UNIT_TEST)


if(MSVC)

	set_target_properties(DecisionTreeTests PROPERTIES COMPILE_FLAGS "/Zm200 /bigobj")

endif()






SET(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})