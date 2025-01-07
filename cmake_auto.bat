@echo off

set root_path=%cd%
echo %root_path%



set QT_PATH=D:\soft\dev\Qt\6.7.3\msvc2019_64\bin
set OPENCV_PATH=D:\soft\dev\opencv-4.10.0\x64\vc16\bin

set TCMALLOC_PATHD=%root_path%\3rdParty\tcmalloc-2.16\debug
set TCMALLOC_PATH=%root_path%\3rdParty\tcmalloc-2.16\release
set ZMQ=%root_path%\3rdParty\zeromq-4.3.5\bin

set path=%path%;%QT_PATH%;%OPENCV_PATH%;%TCMALLOC_PATHD%;%TCMALLOC_PATH%;%ZMQ%

echo %path%
pause


echo "---------step, cmake Doit"
cd %root_path%
set build_path=%root_path%\build
echo %build_path%

if exist %build_path% (
	rmdir /s/q %build_path%
)

mkdir %build_path%
cd %build_path%


cmake ..



echo "---------step, launch vs2019"
start devenv %root_path%\build\Doit.sln
pause
