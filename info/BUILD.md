# Building and using the Houzi Game Engine



## Building
Currently only builds on Windows with the MinGW compiler are supported.
Support for more platforms and compilers is coming soon.



### Configuring the project with CMake
The Houzi Game Engine uses CMake to control the compilation process.
When configuring the project with CMake, the following options are available:

* **CMAKE\_BUILD\_TYPE**: set to "Release" to build optimized, faster binaries, or to "Debug" to build debugging-friendly binaries.

* **HOU\_CFG\_BUILD\_\[library\_identifier\]**: if set, the corresponding library will be built.
If unset, the library will not be built.
When building a library be careful to also build its dependencies.

* **HOU\_CFG\_BUILD\_\[library\_identifier\]\_TESTS**: if set, the tests for the corresponding library will be built.
If unset, the tests will not be built.
Be careful to build the corresponding library when building the relative tests.
To build the tests you must have downloaded and built the gtest library.
CMake will try to detect the path to the gtest library and the gtest header files by itself.
In case it cannot do this, you can manually set **LIB\_GOOGLE\_TEST** to the path to the library and **LIB\_GOOGLE\_TEST\_INCLUDE\_DIR** to the path to the library headers.

* **HOU\_CFG\_BUILD\_DEMOS**: if set, builds some small demo applications using the Houzi Game Engine.
If unset, the demo applications will not be built.
When building the demo applications, pay attention to build all of the Houzi Game Engine libraries.

* **HOU\_CFG\_BUILD\_OPENAL\_SOFT**: if set, OpenALSoft will be built and used as the low-level sound library.
If unset, CMake will try to detect the path to an installed OpenAL library implementation and its headers.
In case it cannot do this, you can manually set **LIB\_OPENAL** to the path to the library and **LIB\_OPENAL\_INCLUDE\_DIR** to the path to the library headers.
When building OpenALSoft, refer to the OpenALSoft documentation for details about the configuration.

* **HOU\_CFG\_STATIC\_LIBS**: if set, static libraries will be build, otherwise shared libraries will be built.
When building static libraries, you should define the preprocessor symbol **HOU\_STATIC** to ensure that including headers from the library will behave correctly.
When building static libraries, all dependencies must be explicitly linked, even if not directly used.

* **HOU\_CFG\_DISABLE\_EXCEPTIONS**: if set, exceptions will be completely disabled.
Instead of throwing an exception, the program will abort and write an error message in the error stream.
If exceptions are disabled, you should define the preprocessor symbol **HOU\_DISABLE\_EXCEPTIONS** to ensure that header files will behave consistently.

* **HOU\_CFG\_ENABLE\_AL\_\[check_type\]\_CHECKS**: these options enables some OpenAL error checks when set.
These checks can be useful during development or when debugging audio issues, but can be expensive and should be enabled for release builds.
When enabling a check of a specific type, the preprocessor symbl **HOU\_ENABLE\_GL\_\[check_type\]\_CHECKS** should be defined to ensure that header files will behave consistently.

* **HOU\_CFG\_ENABLE\_GL\_\[check_type\]\_CHECKS**: these options enables some OpenGL error checks when set.
These checks can be useful during development or when debugging graphics issues, but can be expensive and should be enabled for release builds.
When enabling a check of a specific type, the preprocessor symbl **HOU\_ENABLE\_AL\_\[check_type\]\_CHECKS** should be defined to ensure that header files will behave consistently.



### Building on Windows with MinGW
* Install [CMake](https://cmake.org/).

* Install [MinGW](http://www.mingw.org/).

* Download and build [gtest](https://github.com/google/googletest).
This is optional and required only if you wish to run the unit tests yourself.

* Create a build directory inside the project root folder.

* Configure the project with the CMake graphical interface inside the build directory.

* Run the following command from the build directory in the Windows command line prompt:

```
mingw32-make
```



### Module dependencies
The dependencies between the modules are as follows:

* **houcor**: no dependencies.

* **houmth**: houcor.

* **housys**: houcor, houmth.

* **hougl**: houcor, housys, OpenGL, GLAD.

* **hougfx**: houcor, houmth, housys, hougl, OpenGL, GLAD, SOIL, Freetype.

* **houal**: houcor, OpenAL.

* **houaud**: houcor, houmth, housys, houal, OpenAL, OGG, VORBIS.

When building only some of the modules, pay attention to build the modules it depends on as well.
The external libraries will automatically be built when required.



## Setting up a project using the Houzi Game Engine
This section contains information to help setting up a project using the Houzi Game Engine.
You can use the [demo applications CMakeLists.txt file](source/demo/CMakeLists.txt) as an example of how to setup a CMake project using the Houzi Game Engine.



### Include directories
The include directories of all used modules should be added to the project.
With CMake this is done with:
```
INCLUDE_DIRECTORIES(<houzi_game_engine_root_folder>/source/<module_name/include)
```



### Linking libraries
The target should be linked to the libraries of all used modules.
With CMake this is done with:
```
TARGET_LINK_LIBRARIES(<target_name> <library_names>)
```



### Defining preprocessor symbols
According to the settings with which the houzi-game-engine has been built, some preprocessor symbols might be to be defined:

* When linking to houzi-game-engine static libraries, the HOU\_STATIC symbol must be defined.

* When linking houzi-game-engine libraries with disabled exceptions, the HOU\_DISABLE\_EXCEPTIONS symbol should be defined.

* When linking to houzi-game-engine libraries with enabled OpenGL error checks, the HOU\_ENABLE\_GL\_CHECKS symbol should be defined.

* When linking to houzi-game-engine libraries with enabled OpenAL error checks, the HOU\_ENABLE\_AL\_CHECKS symbol should be defined.

* When linking to houzi-game-engine Debug libraries, the HOU\_DEBUG symbol should be defined.
