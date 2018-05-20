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

## Building
Server side of the application is built using [Gradle](https://gradle.org/).

Client side solution is built using [CMake](https://cmake.org/).

1. Clone the repository and initialize submodules:

    ```git clone —recurse-submodules -j8 git@github.com:Zukkari/zshare.git```

1. Move into the project folder:

    ```cd zshare```

1. Build the server:

      1. Move into the server folder: 
      
            ```cd zshare-server```
        
       
      1. Build the ```jar```:
      
            ```./gradlew jar```
        
      1. Server ```jar``` file is now located in ```{pathToRepo}/zshare-sever/build/libs/zshare-server-1.0-SNAPSHOT.jar```
      and can be started by running ```java -jar {pathToJar}```. This will start the server on port 8080.

1. Build the client:

    1. Move into the client folder: 
    
        ```cd zshare-client```
        
    1. Execute CMake:
    
         ```cmake .```
        
    1. Run ```Makefile```:
    
        ```make```
        
    1. Binary executable will be created with the name ```zshr```.

## Using the program

Program has 2 main functions:

1. Sending the file:

```./zshr send <path to file>```

Optionally file name for the receiver can be used:
```./zshr send <path to file> <new file name>```

After sending the file the program will notify you with the code:
```
Your file '<example file name>' has been successfully uploaded.
The code is => <code>
```
Now the ```<code>``` can be used to share the file.


1. Receiveing the file:

```./zshr receive <code>```

Where code is the code generated in the first step.
You will be then prompted to save the file or to skip saving the file.
Note that file will only be saved if you accept it, otherwise it will remain on the server.
