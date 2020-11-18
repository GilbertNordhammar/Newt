@echo off
pushd %~dp0\..\
echo %cd%
call thirdparty\bin\premake5.exe vs2019
popd
PAUSE