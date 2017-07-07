cmake_minimum_required(VERSION 3.0)

project(DecisionTree VERSION 1.0)

list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.6/msvc2013)
list(APPEND CMAKE_PREFIX_PATH C:/Qt/5.7/msvc2013)

find_package(Qt5 COMPONENTS Core Gui Widgets SerialPort PrintSupport Svg Sql Network Multimedia)
get_target_property (QT_QMAKE_EXECUTABLE Qt5::qmake LOCATION)

# Let's do the cmake job for us
set(CMAKE_AUTOMOC OFF) # For meta object compiler
set(CMAKE_AUTORCC ON) # Resource files
set(CMAKE_AUTOUIC ON) # UI files

set(BOOST_COMPILER "vc120")
set(BOOST_VERSION "1_57")
set(BOOST_CONFIG_DEBUG "mt-gd")
set(BOOST_CONFIG_RELEASE "mt")

set(BOOST_DIR C:/boost_${BOOST_VERSION}_0)
set(BOOST_ROOT C:/boost_${BOOST_VERSION}_0)
set(BOOST_LIBRARYDIR ${BOOST_DIR}/stage/lib)
set(BOOST_INCLUDEDIR ${BOOST_DIR}/boost)
list(APPEND CMAKE_PREFIX_PATH ${BOOST_DIR} ${BOOST_LIBRARYDIR})
set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost
             COMPONENTS chrono
                        system
                        math_c99
                        container
             REQUIRED)

if(EXISTS "C:/Users/nahrstaedt/Documents/svn/MultiEMBI/Software" AND IS_DIRECTORY "C:/Users/nahrstaedt/Documents/svn/MultiEMBI/Software")
	set(MultiEMBI_SVN_DIR C:/Users/nahrstaedt/Documents/svn/MultiEMBI)
elseif(EXISTS "C:/Users/Benjamin/Documents/Projekte/Software" AND IS_DIRECTORY "C:/Users/Benjamin/Documents/Projekte/Software")
	set(MultiEMBI_SVN_DIR C:/Users/Benjamin/Documents/Projekte)
else()
	message(FATAL_ERROR "MultiEMBI directory not found!")
endif()

set(EDFlib_DIR ${MultiEMBI_SVN_DIR}/Software/EDFlib)
add_subdirectory(${EDFlib_DIR}/src ${CMAKE_SOURCE_DIR}/lib/EDFlib)
set(EDFlib_INCLUDE_DIRS  ${EDFlib_DIR}/src)
set(EDFlib_DEBUG_LIBRARIES  ${CMAKE_SOURCE_DIR}/lib/EDFlib/Debug/EDFlibd.lib)
set(EDFlib_RELEASE_LIBRARIES  ${CMAKE_SOURCE_DIR}/lib/EDFlib/Release/EDFlib.lib)

set(CoreLib_DIR ${MultiEMBI_SVN_DIR}/Software/CoreLib)
add_subdirectory(${CoreLib_DIR}/src ${CMAKE_SOURCE_DIR}/lib/CoreLib)
set(CoreLib_INCLUDE_DIRS  ${CoreLib_DIR}/src)
set(CoreLib_DEBUG_LIBRARIES  ${CMAKE_SOURCE_DIR}/lib/CoreLib/Debug/CoreLibd.lib)
set(CoreLib_RELEASE_LIBRARIES  ${CMAKE_SOURCE_DIR}/lib/CoreLib/Release/CoreLib.lib)

include_directories(${BOOST_DIR})
include_directories(${CoreLib_INCLUDE_DIRS})


add_subdirectory(src ${CMAKE_SOURCE_DIR}/lib/DecisionTree)
#add_subdirectory(unitTests ${CMAKE_SOURCE_DIR}/buildUnitTest)