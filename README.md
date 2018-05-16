# zshare
File sharing program made as a course project for C++ course in University of Tartu.

## Goal
Goal is to build an application similar(read 'clone for educational purposes') to [wormhole](https://github.com/warner/magic-wormhole):

1. Client application declares to server that it wants to share the file:
    1. Uploads file to the server
    1. Server sends back a code in human readable format - this code can be shared with a person you want to share a file with.
1. Another client application connects to the server, asks for the file metadata with a given code.
    1. If client wants to download the file, application sends another request to download the content of the file.
1. When file is received by one of the clients, file is deleted from the server.

## Tools
The application constists of two parts:
1. Server, written in Kotlin using [Ktor](https://github.com/ktorio/ktor) framework.
1. Client side solution using C++:
    1. CLI
    1. Qt GUI

## Building
1. Server side of the application is build using [Gradle](https://gradle.org/)
1. Client side solution is build using [CMake](https://cmake.org/)
