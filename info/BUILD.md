# Building and using the Houzi Game Engine



## Building
The following platforms are currently supported:

* Windows with MinGW64.

* Windows with Visual Studio.

* Linux with GCC.



### Configuring the project with CMake
The Houzi Game Engine uses CMake.
When configuring the project with CMake, the following options are available:

* **CMAKE\_BUILD\_TYPE**: set to "Release" to build optimized libraries, or to "Debug" to build debug libraries.
When linking to debug libraries, you should define the preprocessor symbol **HOU\_DEBUG** to enxure that header files will behave consistently.

* **HOU\_CFG\_BUILD\_TESTS**: if set, the test executables will be built.
If unset, the tests will not be built.

* **HOU\_CFG\_BUILD\_GOOGLE\_TEST**: if set, the gtest library will be built.
If unset, CMake will try to detect the path to an installed gtest library and its headers.
In case it fails to detect the library, you can manually set **LIB\_GOOGLE\_TEST** to the path to the library and **LIB\_GOOGLE\_TEST\_INCLUDE\_DIR** to the path to the library headers.
When building gtest, refer to the gtest documentation for details about the configuration.
This option will only appear if **HOU\_CFG\_BUILD\_TESTS** is on.

* **HOU\_CFG\_BUILD\_DEMOS**: if set, some demo applications will be built.
If unset, the demo applications will not be built.

* **HOU\_CFG\_BUILD\_OPENAL\_SOFT**: if set, OpenALSoft will be built and used as the low-level sound library.
If unset, CMake will try to detect the path to an installed OpenAL library implementation and its headers.
In case it fails to detect the library, you can manually set **LIB\_OPENAL** to the path to the library and **LIB\_OPENAL\_INCLUDE\_DIR** to the path to the library headers.
When building OpenALSoft, refer to the OpenALSoft documentation for details about the configuration.

* **HOU\_CFG\_BUILD\_SDL2**: if set, SDL2 will be built and used.
If unset, CMake will try to detect the path to an installed SDL2 library and its headers.
In case if fails to detect the library, you can manually set **LIB\_SDL2** to the path to the library and **LIB\_SDL2\_INCLUDE\_DIR** to the path to the library headers.
When building SDL, refer to the SDL documentation for details about the configuration.

* **HOU\_CFG\_BUILD\_STATIC\_LIBS**: if set, static libraries will be build, otherwise shared libraries will be built.
When building static libraries, you should define the preprocessor symbol **HOU\_STATIC** to ensure that import attributes will be defined correctly.
When building static libraries, all dependencies of the employed libraries must be explicitly linked, even if not directly used.

* **HOU\_CFG\_DISABLE\_EXCEPTIONS**: if set, exceptions will be completely disabled.
Instead of throwing an exception, the program will terminate and write an error message in the error stream.
If exceptions are disabled, you should define the preprocessor symbol **HOU\_DISABLE\_EXCEPTIONS** to ensure that header files will behave consistently.

* **HOU\_CFG\_ENABLE\_AL\_ERROR\_CHECKS**: if set, several OpenAL checks are activated.
These checks can be useful during development or when debugging audio issues, but can be expensive and should be enabled for release builds.
When enabling OpenAL error checks, the preprocessor symbol **HOU\_ENABLE\_AL\_ERROR\_CHECKS** should be defined to ensure that header files will behave consistently.

* **HOU\_CFG\_ENABLE\_GL\_ERROR\_CHECKS**: if set, several OpenGL error checks are activated.
These checks can be useful during development or when debugging graphics issues, but can be expensive and should be enabled for release builds.
When enabling OpenGL error checks, the preprocessor symbol **HOU\_ENABLE\_GL\_ERROR\_CHECKS** should be defined to ensure that header files will behave consistently.



### Building on Windows with MinGW64
* Install [CMake](https://cmake.org/).

* Install [MinGW](http://www.mingw.org/).

* Create a build directory inside the project root folder.

* Configure the project with the CMake graphical interface inside the build directory.

* Run the following command from the build directory in the Windows command line prompt:
```
mingw32-make
```



### Building on Windows with Visual Studio
For a complete description on how to use CMake with Visual Studio you can refer to [this page](https://blogs.msdn.microsoft.com/vcblog/2016/10/05/cmake-support-in-visual-studio/#configure-cmake).

* Open the root Houzi Game Engine folder with "File > Open > Folder".

* Visual Studio should automatically try to configure the project and generate the CMake cache.
  The cache can be managed manually from the "CMake > Cache (...)" menu.

* You can change the CMake settings for different build configurations by editing the generated CMakeSettings.json file.
```
"configurations": [
  {
    "name": "deb-exc-dyn",
    ...
    "variables": [
      {
        "name": "HOU_CFG_ENABLE_AL_ERROR_CHECKS",
        "value": "ON"
      },
      {
        "name": "HOU_CFG_ENABLE_GL_ERROR_CHECKS",
        "value": "ON"
      }
    ]
    ...
  }
```

* You can build the project by selecting the appropriate build configuration and running "CMake > Build All".



### Building on linux with GCC

* Required packages:

    * cmake.

    * ccmake (optional).

    * make.

    * gcc.

    * OpenGL dev libraries (package xorg-dev, mesa-common-dev, libgl1-mesa-dev on ubuntu).

* Configure with cmake.

* Build with make.



### Building with Emscripten

* Known limitations:

  * Multithreading is not supported.

  * Input files must be preloaded or embedded.

  * Files cannot be written (they technically can in preloaded folders, but won't show up in the real filesystem).

  * Minimizing or maximizing a window is not possible.

  * Making a window resizable is not possible.

  * Making a window bordered is not possible.

  * Focusing a window is not possible.



### Module dependencies
The dependencies between the modules are as follows:

* **houcor**: no dependencies.

* **houmth**: houcor.

* **housys**: houcor, houmth, SDL2, SOIL.

* **hougl**: houcor, housys, OpenGL, GLAD, SDL2.

* **hougfx**: houcor, houmth, housys, hougl, Freetype.

* **houal**: houcor, OpenAL.

* **houaud**: houcor, houmth, housys, houal, OGG, VORBIS.

There is a test executable associated to each module, named **<module_name>-test**.
Each test executable depends on the associated libraries, on its dependencies, and on gtest.



## Setting up a project using the Houzi Game Engine
This section contains information to help setting up a project using the Houzi Game Engine.
You can use the [demo applications CMakeLists.txt file](../source/demo/CMakeLists.txt) as an example of how to setup a CMake project using the Houzi Game Engine.



### Include directories
The include directories of all used modules should be added to the project.
With CMake this is done with:
```
INCLUDE_DIRECTORIES(<houzi_game_engine_root_folder>/source/<module_name/include)

# Example
INCLUDE_DIRECTORIES(${LIB_HOU_PATH}/source/houcor/include)
INCLUDE_DIRECTORIES(${LIB_HOU_PATH}/source/houmth/include)
```



### Linking libraries
The target should be linked to the libraries of all used modules.
With CMake this is done with:
```
TARGET_LINK_LIBRARIES(<target_name> <library_names>)

# Example
TARGET_LINK_LIBRARIES(my_game, houcor houmth)
```



### Defining preprocessor symbols
According to the settings with which the houzi-game-engine has been built, some preprocessor symbols might have to be defined:

* When linking to houzi-game-engine Debug libraries, the **HOU\_DEBUG** symbol should be defined.

* When linking to houzi-game-engine static libraries, the **HOU\_STATIC** symbol should be defined.

* When linking houzi-game-engine libraries with disabled exceptions, the **HOU\_DISABLE\_EXCEPTIONS** symbol should be defined.

* When linking to houzi-game-engine libraries with enabled OpenGL error checks, the **HOU\_ENABLE\_GL\_ERROR\_CHECKS** symbol should be defined.

* When linking to houzi-game-engine libraries with enabled OpenAL error checks, the **HOU\_ENABLE\_AL\_ERROR\_CHECKS** symbol should be defined.

With CMake symbols can be defined with:
```
ADD_DEFINITIONS(-D<symbol_name>)

# Example
ADD_DEFINITIONS(-DHOU_DEBUG)
ADD_DEFINITIONS(-DHOU_ENABLE_GL_ERROR_CHECKS)
```
