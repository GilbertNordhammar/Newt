@echo off
pushd %~dp0\..\

pushd Jerboa\thirdparty
call Win-gen-external-proj.bat
popd

call thirdparty\bin\premake5.exe vs2019

popd
PAUSE