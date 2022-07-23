@echo off

pushd %~dp0\..\..\
call Win-gen-external-proj.bat


pushd dev
call thirdparty\bin\premake5.exe vs2019
popd

popd
PAUSE