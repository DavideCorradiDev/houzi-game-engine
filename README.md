# Houzi Game Engine
The Houzi Game Engine is a C++ open-source, cross-platform library for the development of 2d games.



## Building and using the Houzi Game Engine
Information on how to build and use the Houzi Game Engine can be found [here](info/BUILD.md).



## Documentation
The documentation for the latest version of the Houzi Game Engine can be found [here](https://davidecorradidev.github.io/houzi-game-engine/).

The documentation for any version of the repository can be generated with [Doxygen](http://www.stack.nl/~dimitri/doxygen/).
Simply run the following command from the project root folder, and html documentation will be generated in the docs folder:

```
doxygen Doxyfile
```



## Modules
The Houzi Game Engine is divided into several modules.

* **Core module (houcor)**: this module contains basic core functionalities used by other modules, such as error handling mechanisms, utility classes and functions, and extensions for the standard library containers.
This module should always be built and linked, since all other modules depend on it.

* **Mathemathics module (houmth)**: this module contains classes representing mathematical entities, such as matrices, quaternions, and transforms.

* **System module (housys)**: this module provides an abstraction of the underlying OS.
In particular, it provides classes and functions to create windows, to read input from the keyboard, the mouse, and game pads, and to read and write files with Unicode support.

* **GL module (hougl)**: the Houzi Game Engine uses OpenGL to render graphics.
This module provides a platform-independent abstraction of OpenGL.
In particular, it allows to easily create an OpenGL Context and provides wrappers to many OpenGL functions, providing additional type safety and error checks.

* **Graphics Module (hougfx)**: this module provides all that is necessary to easily render 2d graphics.

* **AL module (houal)**: the Houzi Game Engine uses OpenAL to render sounds.
This module provides wrappers to many OpenAL functions, providing additional type safety and error checks.

* **Audio module (houaud)**: this module provides all that is necessary to play sounds and music, and to read sound files.



## Copyright and license
The Houzi Game Engine is distributed under the [MIT License](LICENSE).

Copyright and license information for the external libraries used in the Houzi Engine can be found [here](info/EXTERNAL_LIBS_INFO.md).
