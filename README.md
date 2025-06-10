# An initializer lib for GLFW, GLAD, OpenGL development in C++

## Build instructions

To build the library, first clone the repo and cd into it. Then execute

```bash
mkdir build
cd build
cmake ..
make
```

After building, you'll get a libInitGL.a file.

## Usage

When compiling your source code, add the libInitGL.a file along with source code files.

```bash
g++ <other files> libInitGL.a
```
or 
```bash
g++ <other files> -L<path to directory containing the libInitGL.a file> -lInitGL
```
