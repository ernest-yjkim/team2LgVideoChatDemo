mkdir X64
mkdir X64\Release
mkdir X64\Debug
copy ..\opencv\build\x64\vc16\bin\opencv_world470.dll X64\Release
copy ..\opencv\build\x64\vc16\bin\opencv_world470d.dll X64\Debug
copy .\libssl-1_1-x64.dll X64\Release
copy .\libssl-1_1-x64.dll X64\Debug
copy .\libcrypto-1_1-x64.dll X64\Release
copy .\libcrypto-1_1-x64.dll X64\Debug