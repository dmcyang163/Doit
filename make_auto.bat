@echo off

set root_path=%cd%
echo %cd%

set path=%path%;D:\soft\dev\Qt\6.7.3\msvc2019_64\bin
echo %path%


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
