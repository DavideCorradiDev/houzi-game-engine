# Houzi Game Engine
The Houzi Game Engine is a C++ open-source, cross-platform library for the development of 2d games.



## Features
The Houzi Game Engine aims to provide the following features:

* **Cross-platform**: provide an abstraction of the underlying operative system and third-party libraries, allowing the same code to be deployed on different platforms (Windows, Linux, Mac OS X, Android, iOS).

* **Reliable**: extensively test and document the code to ensure its reliability, and write the code so that it is hard to make mistakes when using it.

* **Modular**: divide the engine into several modules, making it possible to cherry-pick the desired modules and replace other modules with custom ones.

* **Extendable**: write the engine so that it is practical to extend its functionality, for example by adding new OpenGL shaders or classes to read image and sound files from new formats.



## Project structure



### Modules
The Houzi Game Engine is divided into several separate modules.
Each module will be built into a separate library.

* **Core module (houcor)**: this module contains basic core functionalities used by other modules, such as error handling mechanisms, utility classes and functions, and extensions for the standard library containers.
This module should normally always be built and linked.

* **Mathemathics module (houmth)**: this module contains classes representing mathematical entities, such as matrices, quaternions, and transforms.

* **System module (housys)**: this module provides an abstraction of the underlying OS.
In particular, it provides classes and functions to create windows, to read input from the keyboard, the mouse, and game pads, and to read and write files with Unicode support.

* **GL module (hougl)**: the Houzi Game Engine uses OpenGL to render graphics.
This module provides a platform-independent abstraction of OpenGL.
In particular, it allows to easily create an OpenGL Context and provides wrappers to many OpenGL functions, providing additional type safety and error checks.
Normally you would never directly use the functionality provided by this module.

* **Graphics Module (hougfx)**: this module provides all that is necessary to render 2d graphics.

* **AL module (houal)**: the Houzi Game Engine uses OpenAL to render sounds.
This module provides wrappers to many OpenAL functions, providing additional type safety and error checks.
Normally you would never directly use the functionality provided by this module.

* **Audio module (houaud)**: this module provides all that is necessary to render sound and read sound files.



### External Libraries
The Houzi Game Engine uses the following third party libraries for low-level operations:

* **OpenGL**: used to render graphics.

* **GLAD**: used to generate OpenGL extension loaders.

* **SOIL**: used to read and write image files.

* **Freetype**: used to read font files and render font glyphs.

* **OpenAL**: used to render sounds.

* **OpenALSoft**: provided as a cross-platform implementation of the OpenAL specification.

* **Ogg** and **Vorbis**: used to read and write compressed Ogg Vorbis sound files.



### Dependencies
The dependencies between the modules are as follows:

* **houcor**: no dependencies.

* **houmth**: houcor.

* **housys**: houcor, houmth.

* **hougl**: houcor, housys, OpenGL, GLAD.

* **hougfx**: houcor, houmth, housys, hougl, OpenGL, GLAD, SOIL, Freetype.

* **houal**: houcor, OpenAL.

* **houaud**: houcor, houmth, housys, houal, OpenAL, OGG, VORBIS.



## Setup
Currently only builds on Windows with the MinGW compiler are supported.
Support for more platforms and compilers is coming soon.

### Configuring the project with CMake
The Houzi Game Engine uses CMake to control the compilation process.
When configuring the project with CMake, the following options are available:

* **CMAKE_BUILD_TYPE**: set to "Release" to build optimized, faster binaries, or to "Debug" to build debugging-friendly binaries.

* **HOU_OPT_SHARED_LIBS**: if set, shared libraries will be built. If unset, static libraries will be built.

* **HOU_OPT_USE_EXCEPTION_HANDLING**: if set, exceptions will be used as an error handling mechanism.
If unset, the library functions will crash with an error message instead of throwing exceptions in case of errors.
Disable this only if your target platform does not have decent exception handling support.

* **HOU_OPT_BUILD_<LibraryIdentifier>**: if set, the corresponding library will be built.
If unset, the library will not be built.
When building a library be careful to also build its dependencies.

* **HOU_OPT_BUILD_<LibraryIdentifier>_TESTS**: if set, the tests for the corresponding library will be built.
If unset, the tests will not be built.
Be careful to build the corresponding library when building the relative tests.
To build the tests you must have downloaded and built the gtest library.
CMake will try to detect the path to the gtest library and the gtest header files by itself.
In case it cannot do this, you can manually set **LIB_GOOGLE_TEST** to the path to the library and **LIB_GOOGLE_TEST_INCLUDE_DIR** to the path to the library headers.

* **HOU_OPT_BUILD_DEMOS**: if set, builds some small demo applications using the Houzi Game Engine.
If unset, the demo applications will not be built.
When building the demo applications, pay attention to build all of the Houzi Game Engine libraries.

* **HOU_OPT_BUILD_OPENAL_SOFT**: if set, OpenALSoft will be built and used as the low-level sound library.
If unset, CMake will try to detect the path to an installed OpenAL library implementation and its headers.
In case it cannot do this, you can manually set **LIB_OPENAL** to the path to the library and **LIB_OPENAL_INCLUDE_DIR** to the path to the library headers.
When building OpenALSoft, refer to the OpenALSoft documentation for details about the configuration.

* **HOU_OPT_DISABLE_AL_\*_CHECKS**: these options disable some OpenAL error checks when set.
These checks can be useful during development or when debugging audio issues, but can be expensive and should be disabled for release builds.

* **HOU_OPT_DISABLE_GL_\*_CHECKS**: these options disable some OpenGL error checks when set.
These checks can be useful during development or when debugging graphics issues, but can be expensive and should be disabled for release builds.



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



## Documentation
The documentation can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
Simply run the following command from the project root folder:

```
doxygen Doxyfile
```


## Authors
* Davide Corradi



## Copyright and license
The Houzi Game Engine is distributed under the [MIT License](LICENSE).

Copyright and license information for the third-party libraries used in the Houzi Engine can be found [here](THIRD-PARTY-LICENSES.md).

