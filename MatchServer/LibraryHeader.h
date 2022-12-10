#pragma once

//#pragma comment(lib, "ws2_32.lib")

#define _SILENCE_CXX20_CISO646_REMOVED_WARNING
#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

#ifdef _DEBUG
#pragma comment(lib, "Protobuf\\_Debug\\libprotobufd.lib")
#pragma comment(lib, "ServerCoreLibrary\\Debug\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedPacket\\Debug\\SharedPacket.lib")
#pragma comment(lib, "PhysicsEngine\\Debug\\PhysicsEngine.lib")
#else
#pragma comment(lib, "Protobuf\\_Release\\libprotobuf.lib")
#pragma comment(lib, "ServerCoreLibrary\\Release\\ServerCoreLibrary.lib")
#pragma comment(lib, "SharedPacket\\Release\\SharedPacket.lib")
#pragma comment(lib, "PhysicsEngine\\Release\\PhysicsEngine.lib")
#endif

/*
//include dir
$(SolutionDir)..\SharedProtobuf\Library\Include
$(SolutionDir)..\Library\nlohmann_library
$(SolutionDir)..\SharedProtobuf\SharedProtobuf\Protobuf
$(SolutionDir)..\Library\
$(SolutionDir)..\PhysicsEngine
$(SolutionDir)..\ServerCoreLibrary\ServerCoreLibrary


//lib dir
$(SolutionDir)..\SharedProtobuf\Library\
$(SolutionDir)..\Library\
*/
