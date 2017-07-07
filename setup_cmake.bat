@echo off

cd /d "%~dp0"
set CURRENT_PATH=%~dp0
set ARCHITECTURE=x86
set COMPILER=VisualStudio

set PROJECT=%CURRENT_PATH%
set BUILD_DIR_ROOT=%CURRENT_PATH%/x86_vs_2013

set CMAKE_ROOT=C:\Program Files\CMake
set PATH=%CMAKE_ROOT%/bin;%PATH%

set CTEST_OUTPUT_ON_FAILURE=ON


call "%VS120COMNTOOLS%vsvars32.bat"
set CMAKE_CONFIG=-G "Visual Studio 12 2013"
set COMMAND=devenv DecisionTree.sln

RD /S /Q "%BUILD_DIR_ROOT%"
mkdir "%BUILD_DIR_ROOT%"
cd "%BUILD_DIR_ROOT%"

@echo on

cmake %CMAKE_CONFIG% "%PROJECT%"
%COMMAND%