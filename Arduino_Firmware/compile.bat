@echo off
set build_dir=%cd%\build
echo "Create build folder: %build_dir% if not exists"
mkdir %build_dir% 2> NUL
pushd build
%cd%\..\Toolchain\cmake-3.23.0-rc5-windows-x86_64\bin\cmake.exe -GNinja .. 
%cd%\..\Toolchain\Ninja\ninja.exe
popd

