# Houzi Game Engine
The Houzi Game Engine is a C++ open-source, cross-platform library for the development of 2d games.



## Features
The Houzi Game Engine aims to provide the following features:

* **Cross-platform**: provide an abstraction of the underlying operative system and third-party libraries, allowing the same code to be deployed on different platforms (Windows, Linux, Mac OS X, Android, iOS).

* **Reliable**: extensively test and document the code to ensure its reliability, and write the code so that it is hard to make mistakes when using it.

* **Modular**: divide the engine into several modules, making it possible to cherry-pick the desired modules and replace other modules with custom ones.

* **Extensible**: write the engine so that it is practical to extend its functionality, for example by adding new OpenGL shaders or classes to read image and sound files from new formats.



## Building and using the Houzi Game Engine
Information on how to build the Houzi Game Engine can be found [here](info/BUILD.md).



## Documentation
The documentation for the latest version of the Houzi Game Engine can be found [here](https://davidecorradidev.github.io/houzi-game-engine/).

The documentation can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
Simply run the following command from the project root folder:

```
doxygen Doxyfile
```



## Modules
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



## Copyright and license
The Houzi Game Engine is distributed under the [MIT License](LICENSE).

Copyright and license information for the external libraries used in the Houzi Engine can be found [here](info/EXTERNAL_LIBS_INFO.md).

