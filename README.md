# PyASGE - Python Bindings for ASGE

|      CI              | status                                                                 |
|----------------------|------------------------------------------------------------------------|
| docs                 | [![Docs Actions Status][actions-docs]][actions-docs-link]              |
| conda.recipe         | [![Conda Actions Status][actions-conda-badge]][actions-conda-link]     |
| pip builds           | [![Pip Actions Status][actions-pip-badge]][actions-pip-link]           |
| [`cibuildwheel`][]   | [![Wheels Actions Status][actions-wheels-badge]][actions-wheels-link]  |

[actions-docs]:            https://github.com/HuxyUK/pyasge/workflows/Sphinx/badge.svg
[actions-docs-link]:       https://github.com/HuxyUK/pyasge/actions?query=workflow%3ASphinx
[actions-badge]:           https://github.com/HuxyUK/pyasge/workflows/Tests/badge.svg
[actions-conda-link]:      https://github.com/HuxyUK/pyasge/actions?query=workflow%3AConda
[actions-conda-badge]:     https://github.com/HuxyUK/pyasge/workflows/Conda/badge.svg
[actions-pip-link]:        https://github.com/HuxyUK/pyasge/actions?query=workflow%3APip
[actions-pip-badge]:       https://github.com/HuxyUK/pyasge/workflows/Pip/badge.svg
[actions-wheels-link]:     https://github.com/HuxyUK/pyasge/actions?query=workflow%3AWheels
[actions-wheels-badge]:    https://github.com/HuxyUK/pyasge/workflows/Wheels/badge.svg

A [pybind11](https://github.com/pybind/pybind11) module designed to work with the
ASGE game engine and built with a CMake-based build system. ASGE is a simple 2D
game framework designed to allow rapid prototyping of games. It provides the minimum
of fuss when it comes to creating windows and moving sprites around the virtual
game-world. Though it had humble beginnings, it's evolved to support a number of
additional features over the years.

## Prerequisites

**On Unix (Linux, OS X)**

* A compiler with C++17 support
* CMake >= 3.14 or Pip 10+
* Ninja or Pip 10+

> Mac OSX support is working, but not fully tested due to lack of hardware access.

**Linux Build Dependencies**
* X11
* brotli
* bz2
* harfbuzz
* libpng
* zlib

**On Windows**

* Visual Studio 2015 or newer (required for all Python versions, see notes below)
* CMake >= 3.14 or Pip 10+


## Installation

Just clone this repository and pip install. Note the `--recursive` option which is
needed for the pybind11 submodule:

```bash
git clone --recursive https://github.com/HuxyUK/pyasge.git
pip install ./pyasge
```

With the `setup.py` file included in this example, the `pip install` command will
invoke CMake and build the module as specified in `CMakeLists.txt`.


## Special notes for Windows

**Compiler requirements**

Pybind11 requires a C++11 compliant compiler, i.e Visual Studio 2015 on Windows.
Unlike regular C extension modules, it's perfectly fine to compile a pybind11
module with a VS version newer than the target Python's VS version. See the
[FAQ] for more details.

**Runtime requirements**

The Visual C++ 2015 redistributable packages are a runtime requirement for this
project. It can be found [here][vs2015_runtime].


## Building the documentation

Documentation for the example project is generated using Sphinx. Sphinx has the
ability to automatically inspect the signatures and documentation strings in
the extension module to generate beautiful documentation in a variety formats.
The following command generates HTML-based reference documentation; for other
formats please refer to the Sphinx manual:

 - `cmake -G Ninja -H. -DASGE_BUILD_DEMOS=OFF -DASGE_ENABLE_DOXYGEN=OFF -Bbuild
   -DCMAKE_BUILD_TYPE=Release`
 - `cmake --build build --config Release -t pyasge_docs`

>The files will be output to the build/docs/html folder.



## License

PyASGE is provided under a MIT License that can be found in the LICENSE
file. By using, distributing, or contributing to this project, you agree to the
terms and conditions of this license.


## Test call

```python
import pyasge
pyasge.INFO("Tis a good day to make a GAME!")
pyasge.ERROR("Oh noooes")
```

[`cibuildwheel`]: https://cibuildwheel.readthedocs.io
[FAQ]: http://pybind11.rtfd.io/en/latest/faq.html#working-with-ancient-visual-studio-2009-builds-on-windows
[vs2015_runtime]: https://www.microsoft.com/en-us/download/details.aspx?id=48145
