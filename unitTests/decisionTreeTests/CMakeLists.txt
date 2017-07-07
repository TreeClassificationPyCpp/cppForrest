#project(DecisionTreeTests)


enable_testing()

 
                               

set(SOURCE_FILES
		
	tst_DecisionTree.cpp
			
	BoostTest.cpp
	
	)
	


set(HEADER_FILES

	BoostTest.h

	)


set(QT_MOC_HEADERS)
foreach(headerFile ${HEADER_FILES} )

        file(STRINGS ${headerFile} var REGEX "Q_OBJECT")

        if(var)

            list(APPEND QT_MOC_HEADERS ${headerFile})

        endif()

endforeach()
 


list(APPEND QT_MOC_SOURCES)
 


if (QT_MOC_HEADERS)

    	qt5_wrap_cpp(QT_MOC_SOURCES ${QT_MOC_HEADERS})

	source_group("Generated Files" FILES ${QT_MOC_SOURCES})

endif()

   
if (USE_PCH)

	activate_precompiled_headers("Pch.h" SRC_FILES)

endif() 
	


add_executable(DecisionTreeTests 
		${SOURCE_FILES}
		${HEADER_FILES} 
		${QT_MOC_SOURCES}
	)




add_test(NAME DecisionTreeTests COMMAND DecisionTreeTests)




include_directories(${BOOST_DIR})

include_directories(${DecisionTreeLib_INCLUDE})



target_link_libraries(DecisionTreeTests   
			Qt5::Core  gtest gmock_main
					 
                      )


target_link_libraries(DecisionTreeTests   debug  ${DecisionTreeLib_DEBUG_LIBRARIES})

target_link_libraries(DecisionTreeTests   optimized   ${DecisionTreeLib_RELEASE_LIBRARIES})

add_dependencies(DecisionTreeTests   DecisionTree gtest gmock_main)



target_include_directories(DecisionTreeTests PUBLIC

			${SwallowingLib_INCLUDE}
                        ${Boost_INCLUDE_DIR}
					${DecisionTreeLib_INCLUDE}
				
)

  
target_compile_definitions(DecisionTreeTests PUBLIC BOOST_ALL_NO_LIB UNIT_TEST)


if(MSVC)

	set_target_properties(DecisionTreeTests PROPERTIES COMPILE_FLAGS "/Zm200 /bigobj")

endif()






SET(EXECUTABLE_OUTPUT_PATH  ${CMAKE_BINARY_DIR})