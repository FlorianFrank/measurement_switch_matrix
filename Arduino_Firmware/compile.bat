@echo off
set build_dir=%cd%\build
echo "Create build folder: %build_dir% if not exists"
mkdir %build_dir% 2> NUL
pushd build
cmake -GNinja .. 
%cd%\..\Toolchain\Ninja\ninja.exe
popd

