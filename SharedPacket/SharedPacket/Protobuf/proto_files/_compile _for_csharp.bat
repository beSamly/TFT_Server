protoc.exe --proto_path=./ --csharp_out=../csharp_output/ *.proto
IF ERRORLEVEL 1 PAUSE