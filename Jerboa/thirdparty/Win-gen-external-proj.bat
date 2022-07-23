@echo off
pushd %~dp0

:: spdlog
if not exist "spdlog\build" (
    mkdir spdlog\build
)
pushd spdlog\build
cmake ..
cmake --build . --config Debug
cmake --build . --config Release
cmake --build . --config RelWithDebInfo
popd

:: assimp
if not exist "assimp\build" (
    mkdir assimp\build
)
pushd assimp\build
cmake ..
cmake --build . --config Debug
cmake --build . --config Release
cmake --build . --config RelWithDebInfo
popd

popd